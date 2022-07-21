#include "main.h"
#include "functions.h"
#include <iostream>
#include "GetImagePath.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define PI 3.141

using namespace std;
int POS_X, POS_Y;

std::string model_name = "Models/Sun.obj";
std::string earth_file = "Models/Earth.obj";
std::string jupiter_file = "Models/Jupiter.obj";
std::string mercury_file = "Models/Mercury.obj";
std::string venus_file = "Models/Venus.obj";
std::string mars_file = "Models/Mars.obj";
std::string saturn_file = "Models/Saturn.obj";
std::string uranus_file = "Models/Uranus.obj";
std::string neptune_file = "Models/Neptune.obj";
std::string trump_file = "Models/Trump.obj";

GLfloat light_pos[] = {0.0f, 0.0f, 500.00f, 1.0f};

void loadIntroScene(void);

float pos_x, pos_y, pos_z;
float angle_x = 0.0f, angle_y = 0.0f;

int x_old = 0, y_old = 0;
int current_scroll = 5;
float zoom_per_scroll;

bool is_holding_mouse = false;
bool is_updated = false;
int multiplier = 2;

int intro_pos_anim_z = 0;

int intro_screen = true;

Model model;
Model earth;
Model jupiter;
Model mercury;
Model venus;
Model mars;
Model saturn;
Model uranus;
Model neptune;
Model trump;

float earth_pos[3];
float mercury_pos[3];
float venus_pos[3];
float mars_pos[3];
float saturn_pos[3];
float jupiter_pos[3];
float uranus_pos[3];
float neptune_pos[3];

int selected = 0;
int planet_bitmap[8] = {0x00000001,
                        0x00000002,
                        0x00000004,
                        0x00000008,
                        0x00000010,
                        0x00000020,
                        0x00000040,
                        0x00000080};
float radius;
bool increment = true;
int sign = 1;
float offset_x = 0;
float offset_y = 0;
int i = 0;

functions* earth_functions;
functions* jupiter_functions;
functions* mercury_functions;
functions* venus_functions;
functions* mars_functions;
functions* saturn_functions;
functions* uranus_functions;
functions* neptune_functions;


float eye[3] = {0.0,0.0,100.0};
float center[3] = {0.0,0.0,0.0};
float up[3] = {0.0,1.0,0.0};

int planet_enabled = 0x000000FF;
int orbit_enabled = 0x000000FF;
int individual_planet = 0x00000001;
bool first = true;
unsigned int introBG;
void menu(int val);
void createMenu();
int first_intro = true;

int intro_pos_anim_z_1 = 0.0;
int intro_pos_anim_z_2 = 0.0;
int intro_pos_anim_z_3 = 0.0;

void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0, 1.7, 1.0, 2000.0);
    gluLookAt(0.0,0.0,200.0,0.0,0.0,0.0,0.0,1.0,0.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    model.load(model_name.c_str());
    earth.load(earth_file.c_str());
    jupiter.load(jupiter_file.c_str());
    mercury.load(mercury_file.c_str());
    venus.load(venus_file.c_str());
    mars.load(mars_file.c_str());
    saturn.load(saturn_file.c_str());
    uranus.load(uranus_file.c_str());
    neptune.load(neptune_file.c_str());
    trump.load(trump_file.c_str());

    pos_x = 0;
    pos_y = 0;
    pos_z = 0;
    earth_pos[0] = pos_x;
    earth_pos[1] = 0;
    earth_pos[2] = pos_z;

    mercury_functions = new functions(4.1, 6);
    venus_functions = new functions(1.5, 8);
    earth_functions = new functions(1, 10);
    mars_functions = new functions(0.53, 12);
    saturn_functions = new functions(0.06,20);
    jupiter_functions = new functions(0.08, 17);
    uranus_functions = new functions(0.04, 23);
    neptune_functions = new functions(0.01, 25);

    radius = abs(10);

    zoom_per_scroll = -model.pos_z / 10.0f;
}


void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    // glColorf(1.0,1.0,1.0,1.0);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex3f(x + cx, y + cy, pos_z);//output vertex 
    }
    glEnd();
}


void drawText(std::string str, float x, float y)
{
    glRasterPos2f(x, y);
    int count = 0;
    for (char c : str)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        count++;
        if (count == 30)
        {
            count = 0;
            y -= 1.2;
            glRasterPos2f(x, y);
        }
    }
}

void Jupiter()
{
    glPushMatrix();
    glTranslatef(offset_x + jupiter_pos[0], offset_y + jupiter_pos[2],  pos_z);
    glScalef(0.5,0.5,0.5);
    glRotatef(angle_y, 0.0, 1.0, 0.0);
    jupiter.draw();
    glPopMatrix();
}

void Mercury()
{
    glPushMatrix();
    glTranslatef(offset_x + mercury_pos[0], offset_y + mercury_pos[2], pos_z);
    glScalef(0.3,0.3,0.3);
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    mercury.draw();
    glPopMatrix();
}

void Venus()
{
    glPushMatrix();
    glTranslatef(offset_x + venus_pos[0], offset_y + venus_pos[2], pos_z);
    glScalef(0.5,0.5,0.5);
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    venus.draw();
    glPopMatrix();
}

void Earth()
{
    glPushMatrix();
    glTranslatef(offset_x + earth_pos[0], offset_y+ earth_pos[2], pos_z);
    glScalef(0.7,0.7,0.7);
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    earth.draw();
    glPopMatrix();
}

void Mars()
{
    glPushMatrix();
    glTranslatef(offset_x + mars_pos[0], offset_y+ mars_pos[2], pos_z);
    glScalef(0.6,0.6,0.6);
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    mars.draw();
    glPopMatrix();
}


void Saturn()
{
    glPushMatrix();
    glTranslatef(offset_x + saturn_pos[0], offset_y+ saturn_pos[2], pos_z);
    glScalef(0.9,0.9,0.9);
    glRotatef(angle_y, 1.0f, 0.0f, 0.0f);
    saturn.draw();
    glPopMatrix();
}

void Uranus()
{
    glPushMatrix();
    glTranslatef(offset_x + uranus_pos[0], offset_y + uranus_pos[2], pos_z);
    glScalef(0.5,0.5,0.5);
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    uranus.draw();
    glPopMatrix();
}

void Neptune()
{
    glPushMatrix();
    glTranslatef(offset_x + neptune_pos[0], offset_y + neptune_pos[2], pos_z);
    glScalef(0.7,0.7,0.7);
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    neptune.draw();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (intro_screen)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        if (intro_pos_anim_z > -1500)
            intro_pos_anim_z -= 25.0;
        if (intro_pos_anim_z_1 > -1500)
            intro_pos_anim_z_1 -= 15.0;
        if (intro_pos_anim_z_2 > -1500)
            intro_pos_anim_z_2 -= 10.0;
        if (intro_pos_anim_z_3 > -1500)
            intro_pos_anim_z_3 -= 8.0;
        glEnable(GL_TEXTURE_2D);
        glColor3f(1, 1, 1);
        glBindTexture(GL_TEXTURE_2D, introBG);
        glBegin(GL_QUADS);
        glVertex3f(-400, -300, intro_pos_anim_z);
        glTexCoord3f(1, 1,1.0);
        glVertex3f(-400, 300, intro_pos_anim_z_1);
        glTexCoord3f(0, 1,1.0);
        glVertex3f(400, 300,intro_pos_anim_z_2);
        glTexCoord3f(0, 0,1.0);
        glVertex3f(400, -300, intro_pos_anim_z_3);
        glTexCoord3f(1, 0,1.0);
        glEnd();
        if (first_intro)
        {
            glRotatef(180.0,0.0,0.0,1.0);
            glTranslatef(0.0,0.0,0.0);
            first_intro = false;
        }
        glFlush();

        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        if (!(individual_planet & 0x10000000)) {
            GLuint list;
            list = glGenLists(1);
            glNewList(list, GL_COMPILE);
            glLoadIdentity();
            glPushMatrix();
            DrawCircle(offset_x, offset_y, mercury_functions->GetRadius(), 20);
            DrawCircle(offset_x, offset_y, venus_functions->GetRadius(), 20);
            DrawCircle(offset_x, offset_y, earth_functions->GetRadius(), 30);
            DrawCircle(offset_x, offset_y, mars_functions->GetRadius(), 30);
            DrawCircle(offset_x, offset_y, jupiter_functions->GetRadius(), 30);
            DrawCircle(offset_x, offset_y, saturn_functions->GetRadius(), 30);
            DrawCircle(offset_x, offset_y, uranus_functions->GetRadius(), 30);
            DrawCircle(offset_x, offset_y, neptune_functions->GetRadius(), 30);
            glTranslatef(offset_x, offset_y, pos_z);
            glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
            // glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
            model.draw();
            glPopMatrix();
            if (planet_enabled & 0x00000004) Earth();
            if (planet_enabled & 0x00000001) Mercury();
            if (planet_enabled & 0x00000002)Venus();
            if (planet_enabled & 0x00000008)Mars();
            if (planet_enabled & 0x00000010)Jupiter();
            if (planet_enabled & 0x00000020)Saturn();
            if (planet_enabled & 0x00000040)Uranus();
            if (planet_enabled & 0x00000080)Neptune();
            glEndList();
            glCallList(list);
        }
        else
        {
            glLoadIdentity();
            glPushMatrix();
            glTranslatef(6.0,0.0,30.0);
            glScalef(4.0,4.0,4.0);
            glRotatef(30.0, 0.0,1.0,0.0);
            trump.draw();
            glPopMatrix();
            glPushMatrix();
            drawText(earth_functions->GetFact(selected), 12, 5);
            glTranslatef(pos_x, pos_y, pos_z + 80.0);
            glScalef(1.0,1.0,1.0);
            glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
            glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
            if (individual_planet & 0x00000004) earth.draw();
            if (individual_planet & 0x00000001) mercury.draw();
            if (individual_planet & 0x00000002) venus.draw();
            if (individual_planet & 0x00000008) mars.draw();
            if (individual_planet & 0x00000010) jupiter.draw();
            if (individual_planet & 0x00000020) saturn.draw();
            if (individual_planet & 0x00000040) uranus.draw();
            if (individual_planet & 0x00000080) neptune.draw();
            glPopMatrix();
        }
    }
    glutSwapBuffers();
}

void timer(int value) {
    if (true) {
        is_updated = false;
        if (angle_y >= 360.0)
            angle_y -= 360.0;
        angle_y += 1;
        if (orbit_enabled & 0x00000004 || first) earth_functions->revolve(earth_pos, multiplier);
        if (orbit_enabled & 0x00000001 || first) mercury_functions->revolve(mercury_pos, multiplier);
        if (orbit_enabled & 0x00000002 || first) venus_functions->revolve(venus_pos, multiplier);
        if (orbit_enabled & 0x00000008 || first) mars_functions->revolve(mars_pos, multiplier);
        if (orbit_enabled & 0x00000010 || first) jupiter_functions->revolve(jupiter_pos, multiplier);
        if (orbit_enabled & 0x00000020 || first) saturn_functions->revolve(saturn_pos, multiplier);
        if (orbit_enabled & 0x00000040 || first) uranus_functions->revolve(uranus_pos, multiplier);
        if (orbit_enabled & 0x00000080 || first) neptune_functions->revolve(neptune_pos, multiplier);
        first = false;
        glutPostRedisplay();
    }
    glutTimerFunc(INTERVAL, timer, 0);
}

void mouse(int button, int state, int x, int y) {
    is_updated = true;

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            x_old = x;
            y_old = y;
            is_holding_mouse = true;
        } else
            is_holding_mouse = false;
    } else if (state == GLUT_UP) {
        switch (button) {
        case 3:
            if (current_scroll > -1000) {
                current_scroll--;
                pos_z += zoom_per_scroll;
            }
            break;
        case 4:
            if (current_scroll < 1500) {
                current_scroll++;
                pos_z -= zoom_per_scroll;
            }
            break;
        }
    }
}

void motion(int x, int y) {
    if (is_holding_mouse) {
        is_updated = true;

        angle_y += (x - x_old);
        x_old = x;
        if (angle_y > 360.0f)
            angle_y -= 360.0f;
        else if (angle_y < 0.0f)
            angle_y += 360.0f;

        angle_x += (y - y_old);
        y_old = y;
        if (angle_x > 90.0f)
            angle_x = 90.0f;
        else if (angle_x < -90.0f)
            angle_x = -90.0f;
    }
}


void keys(unsigned char c, int x, int y)
{
    if (c == '1') intro_screen = false;
    if (c == 'z') multiplier++;
    if (c == 'x')
    {
        if (multiplier >= 3)
        {
            multiplier--;
        }
    }
    switch (c)
    {
    case 'a' : offset_x--; break;
    case 'd' : offset_x++; break;
    case 's' : offset_y--; break;
    case 'w' : offset_y++; break;
    case 'm' : if (individual_planet | 0x10000000) {
                selected++;
                if (selected > 7)
                    selected = 0;
                individual_planet = planet_bitmap[selected] | 0x10000000;
            }   
            break;
    default:
        break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    // glutSetOption(GLUT_MULTISAMPLE, 8);
    POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
    POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Load Model");
    init();
    loadIntroScene();
    glutDisplayFunc(display);
    createMenu();
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keys);
    glutMotionFunc(motion);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}


void menu(int val)
{
    if (val & 0x10000000)
    {
        individual_planet = val;
        return;
    }
    if (val & 0x01000000)
    {
        orbit_enabled |= val;
    }
    else
    {
        orbit_enabled &= ~val; 
    }
    individual_planet = 0x0;
}


void createMenu()
{
    int enable_menu = glutCreateMenu(menu);
    glutAddMenuEntry("Mercury",0x01000001);
    glutAddMenuEntry("Venus",0x01000002);
    glutAddMenuEntry("Earth",0x01000004);
    glutAddMenuEntry("Mars",0x01000008);
    glutAddMenuEntry("Jupiter",0x01000010);
    glutAddMenuEntry("Saturn",0x01000020);
    glutAddMenuEntry("Uranus",0x01000040);
    glutAddMenuEntry("Neptune",0x01000080);
    int disable_menu = glutCreateMenu(menu);
    glutAddMenuEntry("Mercury",0x00000001);
    glutAddMenuEntry("Venus",0x00000002);
    glutAddMenuEntry("Earth",0x00000004);
    glutAddMenuEntry("Mars",0x00000008);
    glutAddMenuEntry("Jupiter",0x00000010);
    glutAddMenuEntry("Saturn",0x00000020);
    glutAddMenuEntry("Uranus",0x00000040);
    glutAddMenuEntry("Neptune",0x00000080);

    int menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Individual Planet", 0x10000001);
    glutAddSubMenu("Enable", enable_menu);
	glutAddSubMenu("Disable", disable_menu);
}



void loadIntroScene(void)
{


    glGenTextures(1,&introBG);
    glBindTexture(GL_TEXTURE_2D,introBG);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    int width = 0, height = 0,channels = 0;


    GetImagePath getImagePath;
    string p = "\\final-intro.bmp";
    char *path = (char*)p.c_str();

    path = getImagePath.getPath(&path,false);
    printf("\nPath is %s\n",path);
    unsigned char *data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);

    // unsigned char *data = stbi_load("C:\\Users\\Hp\\CGV\\Achievements-of-ISRO-opengl-project\\final-intro.psd", &width, &height, &channels, STBI_rgb_alpha);

    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    }
    else
    {
    
        std::cout << "Failed to load intro slide" << std::endl;
    }
    stbi_image_free(data);
    std::cout << "done" << std::endl;


    /* Night background loading */
    // glGenTextures(1,&nightBG);
    // glBindTexture(GL_TEXTURE_2D,nightBG);

    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    // path = "\\images\\psds\\nightBG.psd";
    // path = getImagePath.getPath(&path,false);
    // //printf("\nAB image 1 Path is %s\n",path);
    // data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    // // printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

    // if(data)
    // {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //     std::cout << "done loading NIGHT BG" << std::endl;
    // }
    // else
    // {
    //     std::cout << "Failed to load NIGHT BG" << std::endl;
    // }
    // stbi_image_free(data);


    // /* END background loading */
    // glGenTextures(1,&endBG);
    // glBindTexture(GL_TEXTURE_2D,endBG);

    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    // path = "\\images\\psds\\ending.psd";
    // path = getImagePath.getPath(&path,false);
    // //printf("\nAB image 1 Path is %s\n",path);
    // data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    // // printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

    // if(data)
    // {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //     std::cout << "done loading END BG" << std::endl;
    // }
    // else
    // {
    //     std::cout << "Failed to load END BG" << std::endl;
    // }
    // stbi_image_free(data);
}

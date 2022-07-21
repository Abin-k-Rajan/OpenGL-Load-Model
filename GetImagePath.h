#ifndef GETIMAGEPATH_H
#define GETIMAGEPATH_H
#include <GL/glut.h>
class GetImagePath
{
public:
    char* getPath(char **path,bool isAk)
    {
        isAk = true;
       // printf("Given path is %s",*path);
        char akPath[] = "C:\\Users\\abins\\Desktop\\data\\Projects\\cgv\\OpenGL-Load-Model\\";
        char pkPath[] = "C:\\Users\\abins\\Desktop\\data\\Projects\\cgv\\OpenGL-Load-Model\\";
        char finalPath[10000];
        if(isAk == true)
        {
            strcpy(finalPath,akPath);
            strcat(finalPath,*path);
            *path = finalPath;
            //printf("final path is %s",*path);
            return *path;
        }

        else
        {

            strcpy(finalPath,pkPath);
            strcat(finalPath,*path);
            *path = finalPath;
            //printf("final path is %s",*path);
            return *path;
        }
        //  return;

    }
};


#endif // GETIMAGEPATH_H
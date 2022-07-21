#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

using namespace std;
class functions
{
private:
    /* data */
    bool increment = true;
    int sign = 1;
    float radius;
    float pos_x;
    float pos_y;
    float pos_z;
    float speed;
    int ang = 0;
public:
    functions(float speed, float radius);
    functions(float pos_x, float pos_y, float pos_z, float speed, float radius);
    ~functions();
    void revolve(float tx[], int multiplier);
    inline float GetRadius() { return radius; }

    string GetFact(int i);
};



#endif
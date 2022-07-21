#include "functions.h"
#include <math.h>
#include <string>
#include <vector>
#define PI 3.141

using namespace std;

functions::functions(float pos_x, float pos_y, float pos_z, float speed, float radius)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_z = pos_z;
    this->speed = speed;
    this->radius = radius;
}

functions::functions(float speed, float radius)
{
    this->speed = speed;
    this->radius = radius;
}

void functions::revolve(float tx[], int multiplier)
{
    ang++;
    float angle = 0.6f * ang * speed * multiplier;
    float x = radius * sin(PI * 2 * angle / 360);
    float y = radius * cos(PI * 2 * angle / 360);
    tx[0] = x;
    tx[2] = y;
}

vector<string> facts= {
    "Mercury takes 59 Earth days to make one full rotation. But a year on Mercury goes fast. Because it's the closest planet to the sun, it goes around the Sun in just 88 Earth days. Visit NASA Space Place for more kid-friendly facts.",
    "Venus is the second planet from the Sun and is named after the Roman goddess of love and beauty. As the brightest natural object in Earth's night sky after the Moon, Venus can cast shadows and can be visible to the naked eye in broad daylight.",
    "Earth is an ellipsoid with a circumference of about 40,000 km. It is the densest planet in the Solar System. Of the four rocky planets",
    "Mars is the fourth planet from the Sun and the second-smallest planet in the Solar System, being larger than only Mercury. In English, Mars carries the name of the Roman god of war.",
    "Jupiter is the fifth planet from the Sun and the largest in the Solar System. It is a gas giant with a mass more than two and a half times that of all the other planets in the Solar System combined, but slightly less than one-thousandth the mass of the Sun.",
    "Saturn is the sixth planet from our Sun (a star) and orbits at a distance of about 886 million miles (1.4 billion kilometers) from the Sun.",
    "Uranus is the seventh planet from the Sun. Its name is a reference to the Greek god of the sky, Uranus, who, according to Greek mythology, was the great-grandfather of Ares, grandfather of Zeus and father of Cronus. It has the third-largest planetary radius and fourth-largest planetary mass in the Solar System.",
    "Neptune is the eighth and farthest-known Solar planet from the Sun. In the Solar System, it is the fourth-largest planet by diameter, the third-most-massive planet, and the densest giant planet. It is 17 times the mass of Earth, and slightly more massive than its near-twin Uranus."
};

string functions::GetFact(int i)
{
    return facts[i];
}
#include "Tuple.h"
#include "easyppm.h"
#include <string>

class Object {
    public:
        Tuple position;
        Tuple normal;
        Tuple point;
        int OBJ_ID;
        float radius;
        int specular;
        ppmcolor color;

        Tuple Normal();
};

class Sphere : public Object {
    public:
        Sphere(Tuple position, ppmcolor color, float radius, int specular);
};

class Plane : public Object {
    public:
        Plane(Tuple position, Tuple normal, ppmcolor color, int specular);
};

class Light {
    public:
        Tuple position;
        Tuple direction;
        string type;
        float intensity;
    
};

class AmbientLight : public Light {
    public:
        AmbientLight(float intensity);
};

class DirectionalLight : public Light {
    public:
        DirectionalLight(Tuple direction, float intensity);
};

class PointLight : public Light {
    public:
        PointLight(Tuple position, float intensity);
};


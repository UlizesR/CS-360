#include "Tuple.h"
#include "easyppm.h"

class Object {
    public : 
        int OBJ_ID; // 1 if it its a sphere and 2 if it's a plane 
        double t;
        Tuple position; // Both plane and sphere can use position. Yay!
        Tuple point;
        ppmcolor color;
        float red;
        float green;
        float blue;

        Tuple normal; // used only if this is a plane

        double radius; // Used only if this is a sphere


        Object *pointerToObject;
        // Constructor that initializes the pointerToObject to NULL
        Object();

        // checks if a ray hits an object
        bool Intersect(Tuple rayOrigin, Tuple rayDirection, Object* object);
        Tuple computeNormal(Object* object);
        friend ostream &operator<<(ostream &os, const Object &Obj);
};

class Sphere : public Object {
    public:
        // constructor that initializes the values that define a sphere
        // and passes it to the set_values function to create the sphere object
        // OBJ_ID = 1
        Sphere(Tuple pos, ppmcolor c, double r);
};

class Plane : public Object {
    public:
        // constructor that initializes the values that define a plane
        // and passes it to the set_values function to create the plane object
        // OBJ_ID = 2
        Plane(Tuple pos, ppmcolor c, Tuple n);
};

class Light {
    public:
        string type;
        float intensity;
        Tuple position;
        Tuple direction;

        Light* pointer_to_light;

        Light();
        float computeLighting(Tuple point, Tuple normal);
};

class AmbientLight : public Light {
    public:
        AmbientLight(float intensity);
};

class DirectionalLight : public Light {
    public: 
        DirectionalLight(float intensity, Tuple direction);
};

class PointLight : public Light {
    public:
        PointLight(float intensity, Tuple position);
};

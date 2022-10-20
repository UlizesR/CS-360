#include "easyppm.h"
#include "Lighting.h"

class Object {
    protected:
        // sets the values that define an object
        // radius and normal vector and default values as depending on the object type they don't need to define
        void set_values(int obj_id, Tuple pos, ppmcolor c, double t, double r = 0, Tuple n = Tuple(1, 1, 1));
        void set_material_values(Rgb specularMaterial, Rgb diffuseMaterial, Rgb ambientMaterial);

    public: 
        int OBJ_ID; // 1 if it its a sphere and 2 if it's a plane 
        double t;
        Tuple position; // Both plane and sphere can use position. Yay!
        ppmcolor color;
        Tuple point;

        Tuple normal; // used only if this is a plane
        Tuple direction;

        double radius; // Used only if this is a sphere
        int specularExponent;

        Rgb specularMaterial;
        Rgb diffuseMaterial;
        Rgb ambientMaterial;

        Rgb specularIntensity; // for non light object
        Rgb diffuseIntensity; // for non light object
        Rgb ambientIntensity;  // for non light object

        Rgb specular;   // for non light object
        Rgb diffuse;   // for non light object
        Rgb ambient;    // for non light object

        Object *pointerToObject;

        // Constructor that initializes the pointerToObject to NULL
        Object();

        // checks if a ray hits an object
        bool Intersection(Tuple rayOrigin, Tuple rayDirection, Object* object);

        friend ostream &operator<<(ostream &os, const Object &Obj);
};

class LightSource : public Object {

    public:

        LightSource(Tuple pos, int specularExponent, Rgb specularIntensity, Rgb diffuseIntensity, Rgb ambientIntensity);
};

class Sphere : public Object {

    Tuple normal;

public:
    // constructor that initializes the values that define a sphere
    // and passes it to the set_values function to create the sphere object
    // OBJ_ID = 1
    Sphere(int obj_id, Tuple pos, ppmcolor c, double r, double t, Rgb specularMaterial, Rgb diffuseMaterial, Rgb ambientMaterial);
};

class Plane : public Object {

public:
    // constructor that initializes the values that define a plane
    // and passes it to the set_values function to create the plane object
    // OBJ_ID = 2
    Plane(int obj_id, Tuple pos, ppmcolor c, Tuple n, double t, Rgb specularMaterial, Rgb diffuseMaterial, Rgb ambientMaterial);
};

#include "object.h"
#include <cmath>

// Constructor that initializes the pointerToObject to NULL
Object::Object() {
    this->pointerToObject = NULL;
}

// checks if a ray hits an object
bool Object::Intersect(Tuple rayOrigin, Tuple rayDirection, Object* object)
{
    // if the object is a sphere
    if (object->OBJ_ID == 1)
    {
        Tuple spherePos_to_rayO = rayOrigin - object->position;
        double a = rayDirection.dot(rayDirection);
        double b = 2 * spherePos_to_rayO.dot(rayDirection);
        double c = spherePos_to_rayO.dot(spherePos_to_rayO) - object->radius * object->radius;
        double discriminant = b * b - 4 * a * c;
        // if discriminant is negative then there is no real solution, in other words no intersection
        if (discriminant < 0)
        {
            object->t = -1;
            return false;
        }
        else
        // if discriminant is positive then there is a solution or one intersection(if discriminant = 0) and two intersections
        // (discriminant > 0) but we want the smallest t value. 
        {
            float t1 = (-b + sqrt(discriminant)) / (2 * a);
            float t2 = (-b - sqrt(discriminant)) / (2 * a);
            object->t = t1 < t2 ? t1 : t2;
            return true;
        }
    }
    // if the object is a plane
    else if (object->OBJ_ID == 2)
    {
        if (object->normal.dot(rayDirection) == 0)
        {
            object->t = -1;
            return false;
        }
        object->t = (object->position - rayOrigin).dot(object->normal) / object->normal.dot(rayDirection);
        return true;
    }
}

Tuple Object::computeNormal(Object *object) {
    if (object->OBJ_ID == 1) {
        Tuple Normal = object->point - object->position;
        Normal.normalize();
        return Normal;
    }
    else if (object->OBJ_ID == 2) {
        Tuple Normal = object->normal;
        Normal.normalize();
        return Normal;
    }
}

    // constructor that initializes the values that define a sphere
    // and passes it to the set_values function to create the sphere object
    // OBJ_ID = 1
    Sphere::Sphere(Tuple pos, ppmcolor c, double r)
{
    this->OBJ_ID = 1;
    this->position = pos;
    this->color = c;
    this->radius = r;
    this->red = c.r;
    this->green = c.g;
    this->blue = c.b;
}

// constructor that initializes the values that define a plane
// and passes it to the set_values function to create the plane object
// OBJ_ID = 2
Plane::Plane(Tuple pos, ppmcolor c, Tuple n)
{
    this->OBJ_ID = 2;
    this->position = pos;
    this->color = c;
    this->normal = n;
    this->red = c.r;
    this->green = c.g;
    this->blue = c.b;
}

Light::Light() {
    pointer_to_light = NULL;
}

float Light::computeLighting(Tuple point, Tuple normal) {
    float i = 0;
    if (this->type == "ambient") {
        i += this->intensity;
    } else {
        if (this->type == "point") {
            Tuple L = this->position - point;
            if (normal.dot(L) > 0) {
                i += (this->intensity * normal.dot(L) / (normal.magnitude() * L.magnitude()));
            }
        } else {
            Tuple L = this->direction;
            if (normal.dot(L) > 0) {
                i += (this->intensity * normal.dot(L) / (normal.magnitude() * L.magnitude()));
            }
        }
    }
    return i;
}

AmbientLight::AmbientLight(float intensity) {
    this->type = "ambient";
    this->intensity = intensity;
}

DirectionalLight::DirectionalLight(float intensity, Tuple direction) {
    this->type = "directional";
    this->intensity = intensity;
    this->direction = direction;
    this->direction.normalize();
}

PointLight::PointLight(float intensity, Tuple position) {
    this->type = "point";
    this->intensity = intensity;
    this->position = position;
}


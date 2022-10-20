#include "object.h"
#include <cmath>

// Constructor that initializes the pointerToObject to NULL
Object::Object() {
    this->pointerToObject = NULL;
}

// sets the values that define an object
// radius and normal vector and default values as depending on the object type they don't need to define
void Object::set_values(int obj_id, Tuple pos, ppmcolor c, double t, double r, Tuple n)
{
    this->OBJ_ID = obj_id;
    this->position = pos;
    this->color = c;
    this->radius = r;
    this->normal = n;
    this->t = t;
}

// checks if a ray hits an object
bool Object::Intersection(Tuple rayOrigin, Tuple rayDirection, Object* object)
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
            object->t = (-b - sqrt(discriminant)) / (2 * a);
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

// constructor that initializes the values that define a sphere
// and passes it to the set_values function to create the sphere object
// OBJ_ID = 1
Sphere::Sphere(int obj_id, Tuple pos, ppmcolor c, double r, double t)
{
    this->OBJ_ID = obj_id;
    this->position = pos;
    this->normal.normalize();
    this->color = c;
    this->radius = r;
    this->t = t;
    Sphere::set_values(this->OBJ_ID, this->position, this->color, this->t, this->radius, this->normal);
}

// constructor that initializes the values that define a plane
// and passes it to the set_values function to create the plane object
// OBJ_ID = 2
Plane::Plane(int obj_id, Tuple pos, ppmcolor c, Tuple n, double t)
{
    this->OBJ_ID = obj_id;
    this->position = pos;
    this->color = c;
    this->normal = n;
    this->t = t;
    Plane::set_values(this->OBJ_ID, this->position, this->color, this->t, 0, this->normal);
}

ostream &operator<<(ostream &os, const Object &Obj)
{
    os << Obj;
    return os;
}
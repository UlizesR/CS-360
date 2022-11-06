#include "objects.h"

Tuple Object::Normal() {
    Tuple Normal;
    if (OBJ_ID == 1) {
        Normal = this->point - this->position;
    } else {
        Normal = this->normal;
    }
    Normal.normalize();
    return Normal;
}

Sphere::Sphere(Tuple position, ppmcolor color, float radius, int specular) {
    this->OBJ_ID = 1;
    this->position = position;
    this->color = color;
    this->radius = radius;
    this->specular = specular;
}

Plane::Plane(Tuple position, Tuple normal, ppmcolor color, int specular)
{
    this->OBJ_ID = 2;
    this->position = position;
    this->normal = normal;
    this->color = color;
    this->specular = specular;
}

AmbientLight::AmbientLight(float intensity) {
    this->type = "Ambient";
    this->intensity = intensity;
}

DirectionalLight::DirectionalLight(Tuple direction, float intensity) {
    this->type = "Directional";
    this->direction = direction;
    this->intensity = intensity;
}

PointLight::PointLight(Tuple position, float intensity) {
    this->type = "Point";
    this->position = position;
    this->intensity = intensity;
}

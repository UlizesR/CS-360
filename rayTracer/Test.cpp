#include "objects.h"
#include "colors.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

void Intersect(Object obj, Tuple rayOrigin, Tuple rayDirection, float t_arr[])
{
    if (obj.OBJ_ID == 1)
    {
        float r = obj.radius;
        Tuple ray_to_sphere = rayOrigin - obj.position;

        float a = rayDirection.dot(rayDirection);
        float b = 2 * rayDirection.dot(ray_to_sphere);
        float c = ray_to_sphere.dot(ray_to_sphere) - r * r;

        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
        {
            t_arr[0] = INFINITY;
            t_arr[1] = INFINITY;
        }
        t_arr[0] = (-b + sqrt(discriminant)) / (2 * a);
        t_arr[1] = (-b - sqrt(discriminant)) / (2 * a);
    }
    else
    {
        if (obj.normal.dot(rayDirection) == 0)
        {
            t_arr[0] = INFINITY;
        }
        t_arr[0] = (obj.position - rayOrigin).dot(obj.normal) / obj.normal.dot(rayDirection);
    }
}

float ComputeLighting(vector<Object> obj_list, vector<Light> light_list, int num_objs, int num_lights, Tuple point, Tuple normal, Tuple direction, int specular)
{
    float intensity = 0;
    direction = direction * -1;
    Tuple L;
    float t_max = 0;
    float t_min = 0.001;
    for (int i = 0; i < num_lights; i++)
    {
        if (light_list[i].type == "Ambient")
        {
            intensity += light_list[i].intensity;
        }
        else
        {
            if (light_list[i].type == "Point")
            {
                L = light_list[i].position - point;
                t_max = 1;
            }
            else
            {
                L = light_list[i].direction;
                t_max = INFINITY;
            }
            // Shadow
            float shadow_t = INFINITY;
            Object *shadow_obj = NULL;
            float t_arr[2];
            for (int i = 0; i < num_objs; i++)
            {
                if (obj_list[i].OBJ_ID == 1)
                {
                    Intersect(obj_list[i], point, L, t_arr);
                    float t1 = t_arr[0];
                    float t2 = t_arr[1];
                    if (t_min <= t1 && t1 <= t_max && t1 <= shadow_t)
                    {
                        shadow_t = t1;
                        shadow_obj = &obj_list[i];
                    }
                    if (t_min <= t2 && t2 <= t_max && t2 <= shadow_t)
                    {
                        shadow_t = t2;
                        shadow_obj = &obj_list[i];
                    }
                }
                else
                {
                    Intersect(obj_list[i], point, L, t_arr);
                    float t = t_arr[0];
                    if ((t_min <= t && t <= t_max && t <= shadow_t))
                    {
                        shadow_t = t;
                        shadow_obj = &obj_list[i];
                    }
                }
            }

            if (shadow_obj != NULL) {
                continue;
            }

            // Diffuse
            float N_dot_L = normal.dot(L);
            if (N_dot_L > 0)
            {
                intensity += ((light_list[i].intensity * N_dot_L) / (normal.magnitude() * L.magnitude()));
            }
            // Specular
            if (specular != -1)
            {
                Tuple R = 2 * normal * normal.dot(L) - L;
                float R_dot_D = R.dot(direction);
                if (R_dot_D > 0)
                {
                    intensity += light_list[i].intensity * pow(R_dot_D / (R.magnitude() * direction.magnitude()), specular);
                }
            }
        }
    }
    return intensity;
}

ppmcolor TraceRay(vector<Object> obj_list, vector<Light> light_list, int num_objs, int num_lights, Tuple rayOrigin, Tuple rayDirection, float t_min, float t_max)
{
    float closest_t = INFINITY;
    Object *closest_obj = NULL;
    float t_arr[2];

    for (int i = 0; i < num_objs; i++)
    {
        if (obj_list[i].OBJ_ID == 1)
        {
            Intersect(obj_list[i], rayOrigin, rayDirection, t_arr);
            float t1 = t_arr[0];
            float t2 = t_arr[1];
            if (t_min <= t1 && t1 <= t_max && t1 <= closest_t)
            {
                closest_t = t1;
                closest_obj = &obj_list[i];
            }
            if (t_min <= t2 && t2 <= t_max && t2 <= closest_t)
            {
                closest_t = t2;
                closest_obj = &obj_list[i];
            }
        }
        else
        {
            Intersect(obj_list[i], rayOrigin, rayDirection, t_arr);
            float t = t_arr[0];
            if ((t_min <= t && t <= t_max && t <= closest_t))
            {
                closest_t = t;
                closest_obj = &obj_list[i];
            }
        }
    }
    if (closest_obj == NULL)
    {
        return white;
    }

    closest_obj->point = rayOrigin + closest_t * rayDirection;
    Tuple Normal = closest_obj->Normal();
    float intensity = ComputeLighting(obj_list, light_list, num_objs, num_lights, closest_obj->point, Normal, rayDirection, closest_obj->specular);

    float new_red = closest_obj->color.r * intensity;
    float new_green = closest_obj->color.g * intensity;
    float new_blue = closest_obj->color.b * intensity;

    return easyppm_rgb(new_red, new_green, new_blue);
}

int main()
{
    int num_objects = 0;

    vector<Object> objectsInMySceneList;
    objectsInMySceneList.push_back(Sphere(Tuple(0, 0, 10, 1), red, 2.5, 2000));
    num_objects++;
    objectsInMySceneList.push_back(Sphere(Tuple(2, 0, 4, 1), blue, 1, 500));
    num_objects++;
    objectsInMySceneList.push_back(Plane(Tuple(0, 0, 10, 1), Tuple(0, 1, -1), cyan, 0));
    num_objects++;
    objectsInMySceneList.push_back(Sphere(Tuple(0, -5001, 0, 1), yellow, 5000, 1000));
    num_objects++;

    int num_lights = 0;
    vector<Light> light_list;
    light_list.push_back(AmbientLight(0.4));
    num_lights++;
    light_list.push_back(DirectionalLight(Tuple(1, 4, 4), 0.2));
    num_lights++;
    light_list.push_back(PointLight(Tuple(2, 1, 0), 0.6));
    num_lights++;

    // Create image of desired dimensions.
    double imageWidth = 1000;
    double imageHeight = 1000;
    PPM myImage = easyppm_create(imageWidth, imageHeight, IMAGETYPE_PPM);

    // Clear all image pixels to RGB color white.
    easyppm_clear(&myImage, white);

    double w = 4;
    double h = 4;
    double z = 4;

    // Axis Vectors
    Tuple X(1, 0, 0, 0);
    Tuple Y(0, 1, 0, 0);
    Tuple Z(0, 0, 1, 0);

    Tuple basePoint(0 - (w / 2), 0 - (h / 2), z, 1);

    for (int j = 0; j < imageHeight; j++)
    {
        for (int i = 0; i < imageWidth; i++)
        {
            Tuple Point = basePoint + (i * w / imageWidth) * X + (j * h / imageHeight) * Y;

            Tuple rayOrigin(0, 0, 0, 1);

            Tuple rayDirection = Point - rayOrigin;
            rayDirection.normalize();

            ppmcolor color = TraceRay(objectsInMySceneList, light_list, num_objects, num_lights, rayOrigin, rayDirection, 1, INFINITY);
            easyppm_set(&myImage, i, j, color);
        }
    }

    easyppm_write(&myImage, "ray_trace5.ppm");
    easyppm_destroy(&myImage);

    // Return error code of 0 to operating system to signal successful exit.
    return 0;
}

#include "object.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    vector<Object *> objectsList;
    objectsList.push_back(new Sphere(Tuple(0, 0, 10, 1), easyppm_rgb(255, 0, 255), 2.5));
    objectsList.push_back(new Sphere(Tuple(2.5, 0, 9, 1), easyppm_rgb(255, 255, 0), 1));;
    // objectsList.push_back(new Plane(Tuple(0, 0, 10, 1), easyppm_rgb(231, 0, 114), Tuple(-1, 0, 1)));
    // objectsList.push_back(new Plane(Tuple(0, 0, 10, 1), easyppm_rgb(21, 80, 114), Tuple(0, 0, -1)));

    // AmbientLight L(0.8);
    DirectionalLight L(0.5, Tuple(0, 1, -1));
    // Create image of desired dimensions.
    double imageWidth = 400;
    double imageHeight = 400;
    PPM myImage = easyppm_create(imageWidth, imageHeight, IMAGETYPE_PPM);

    // Clear all image pixels to RGB color white.
    easyppm_clear(&myImage, easyppm_rgb(255, 255, 255));

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

            double t_min = INFINITY;

            for (int k = 0; k < objectsList.size(); k++)
            {

                if (objectsList[k]->Intersect(rayOrigin, rayDirection, objectsList[k]) && objectsList[k]->t < t_min)
                {
                    t_min = objectsList[k]->t;
                    objectsList[k]->point = rayOrigin + t_min * rayDirection;

                    float L_intensity = L.computeLighting(objectsList[k]->point, objectsList[k]->computeNormal(objectsList[k]));
                    cout << "Lighting: " << L_intensity << endl;
                    cout << "Normal: " << objectsList[k]->computeNormal(objectsList[k]) << endl;

                    cout << "red: " << objectsList[k]->red * L_intensity << " green: " << objectsList[k]->green * L_intensity << " blue: " << objectsList[k]->blue * L_intensity << "\n" << endl;

                    objectsList[k]->color = easyppm_rgb(objectsList[k]->red * L_intensity, objectsList[k]->green * L_intensity, objectsList[k]->blue * L_intensity);
                    easyppm_set(&myImage, i, j, objectsList[k]->color);
                }
            }
        }
    }

    easyppm_write(&myImage, "test.ppm");
    easyppm_destroy(&myImage);

    // To prevent memory leaks, don't really know what this means or how it works
    for (vector<Object *>::iterator it = objectsList.begin(); it != objectsList.end(); ++it)
        delete *it;
    objectsList.clear();

    // Return error code of 0 to operating system to signal successful exit.
    return 0;
}
// objectsList[k]->point = rayOrigin + t_min * rayDirection;

// if (objectsList[k]->OBJ_ID == 1) {
//     objectsList[k]->normal = objectsList[k]->point - objectsList[k]->position;
//     objectsList[k]->normal.normalize();
// }

// float intensity = L.computeLighting(objectsList[k]->point, objectsList[k]->normal);
// float red = objectsList[k]->red * intensity;
// float green = objectsList[k]->green * intensity;
// float blue = objectsList[k]->blue * intensity;

// objectsList[k]->color = easyppm_rgb(red, green, blue);
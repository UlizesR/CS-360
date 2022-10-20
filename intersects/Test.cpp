#include "object.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int main()
{

    vector<Object*> objectsInMySceneList;
    int num_objects = 0;

    Object* S = new Sphere(1, Tuple(0, 0, 10, 1), easyppm_rgb(255, 0, 255), 2.5, 0);
    objectsInMySceneList.push_back(S);
    num_objects++;

    Object* S1 = new Sphere(1, Tuple(2.5, 0, 9, 1), easyppm_rgb(255, 255, 0), 1, 0);
    objectsInMySceneList.push_back(S1);
    num_objects++;

    Object *P = new Plane(2, Tuple(0, 0, 10, 1), easyppm_rgb(231, 0, 114), Tuple(-1, 0, 1), 0);
    objectsInMySceneList.push_back(P);
    num_objects++;

    Object *P1 = new Plane(2, Tuple(0, 0, 10, 1), easyppm_rgb(21, 80, 114), Tuple(0, 0, -1), 0);
    objectsInMySceneList.push_back(P1);
    num_objects++;

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

            for (int k = 0; k < objectsInMySceneList.size(); k++) {

                if (objectsInMySceneList[k]->Intersection(rayOrigin, rayDirection, objectsInMySceneList[k]) && objectsInMySceneList[k]->t < t_min)
                {
                    t_min = objectsInMySceneList[k]->t;
                    easyppm_set(&myImage, i, j, objectsInMySceneList[k]->color);
                }
            }
        }
    }

    easyppm_write(&myImage, "test.ppm");
    easyppm_destroy(&myImage);

    // To prevent memory leaks, don't really know what this means or how it works
    for (vector<Object *>::iterator it = objectsInMySceneList.begin(); it != objectsInMySceneList.end(); ++it)
        delete *it;
    objectsInMySceneList.clear();

    // Return error code of 0 to operating system to signal successful exit.
    return 0;
}

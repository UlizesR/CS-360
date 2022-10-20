#include "object.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    vector<Object *> objectsInMySceneList;
    // vector<Object *> LightSourceList;

    Object *S = new Sphere(1, Tuple(0, 0, 10, 1), easyppm_rgb(255, 0, 0), 2.5, 0, Rgb(0.1, 0.1, 0.1), Rgb(0.8, 0.8, 0.8), Rgb(0.5, 0.5, 0.5));
    objectsInMySceneList.push_back(S);

    Object *S2 = new Sphere(1, Tuple(0, 0, 6, 1), easyppm_rgb(255, 255, 0), 1, 0, Rgb(0.8, 0.8, 0.8), Rgb(0.8, 0.8, 0.8), Rgb(0.5, 0.5, 0.5));
    objectsInMySceneList.push_back(S2);

    Object *P = new Plane(2, Tuple(0, 0, 10, 1), easyppm_rgb(110, 100, 214), Tuple(-1, 0, 1), 0, Rgb(0.8, 0.8, 0.8), Rgb(0.8, 0.8, 0.8), Rgb(0.5, 0.5, 0.5));
    objectsInMySceneList.push_back(P);

    Object *L1 = new LightSource(Tuple(0, 0, 0, 1), 2, Rgb (0.9, 0.9, 0.9), Rgb (0.9, 0.9, 0.9), Rgb (1, 1, 1));
    // LightSourceList.push_back(L1);

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
            
            Tuple rayNormal = rayDirection;
            rayNormal.normalize();

            double t_min = INFINITY;

            for (int k = 0; k < objectsInMySceneList.size(); k++)
            {
                if (objectsInMySceneList[k]->Intersection(rayOrigin, rayNormal, objectsInMySceneList[k]) && objectsInMySceneList[k]->t < t_min)
                {

                    t_min = objectsInMySceneList[k]->t;
                    objectsInMySceneList[k]->point = rayOrigin + objectsInMySceneList[k]->t * rayDirection;
                    easyppm_set(&myImage, i, j, objectsInMySceneList[k]->color);
                }
                
            }
        }
    }

    easyppm_write(&myImage, "testray.ppm");
    easyppm_destroy(&myImage);

    // To prevent memory leaks, don't really know what this means or how it works
    for (vector<Object *>::iterator it = objectsInMySceneList.begin(); it != objectsInMySceneList.end(); ++it)
        delete *it;
    objectsInMySceneList.clear();

    // Return error code of 0 to operating system to signal successful exit.
    return 0;
}
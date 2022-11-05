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

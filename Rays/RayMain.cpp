#include <stdio.h>
#include <cmath>
#include "easyppm.h"
#include "ray.h"


int main() {
	// Create image of desired dimensions.
	double imagePixelSize = 200;
	PPM myImage = easyppm_create(imagePixelSize, imagePixelSize, IMAGETYPE_PPM);

    // Clear all image pixels to RGB color white.
	easyppm_clear(&myImage, easyppm_rgb(255, 255, 255));

	double w = 4;
    double h = 4;
    double z = 4;

    Ray R;

    // Axis Vectors
    Tuple X(1, 0, 0, 0);
    Tuple Y(0, 1, 0, 0);
    Tuple Z(0, 0, 1, 0);

    // Base Point
    Tuple B(0 - (w/2), 0 - (h/2), z, 1);

    for (int i = 0; i < imagePixelSize; i++)
    {

        for (int j = 0; j < imagePixelSize; j++)
        {

            float stepX = i / (imagePixelSize / w);
            float stepY = j / (imagePixelSize / h);

            // P = B + i*X + j*Y
            // P = (-w/2, -h/2, z, 1) + i*(1, 0, 0, 0) + j*(0, 1, 0, 0)
            // P = (-w/2, -h/2, z, 1) + (i, 0, 0, 0) + (0, j, 0, 0)
            // P = (-w/2, -h/2, z, 1) + (i, j, 0, 0)
            // P = (i - w/2, j - h/2, z, 1)
            Tuple P = B + stepX * X + stepY * Y;
            P.print();

            // Vector OP = P - O
            R.direction = (P - R.origin);

            R.direction.normalize();

            double angle = acos(R.direction.dot(Z)/ (R.direction.magnitude() * Z.magnitude()));
            cout << "Angle = " << angle << endl;    
            double value = round(angle * 255);

            easyppm_set(&myImage, i, j, easyppm_rgb(value, value, value));
        }
    }

    easyppm_write(&myImage, "ray_image.ppm");
	easyppm_destroy(&myImage);
    

	// Return error code of 0 to operating system to signal successful exit.
	return 0;
}
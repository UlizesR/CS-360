#include <stdio.h>

#include "easyppm.h"

// Discovery activity
// Step 1. Build and run the image test program from sources test.c and easyppm.c
//         View the resulting output image. Do you see the left half red, and the right half white?
// Step 2. Edit test.c to change the image dimensions to be 200 x 200.
//         Edit the nested loop so that it draws a blue rectangle on the right half of the image.
//         View the resulting output image to check if it worked.

int main() {
	// Create image of desired dimensions.
	int myImageWidth = 200;
	int myImageHeight = 200;
	PPM myImage = easyppm_create(myImageWidth, myImageHeight, IMAGETYPE_PPM);

  // Clear all image pixels to RGB color white.
	easyppm_clear(&myImage, easyppm_rgb(255, 255, 255));

	// Nested outer loop over rows of image...
	for(int y = 0; y < myImageHeight; y++)
		// Nested inner loop over columns of image...
		for(int x = 0; x < myImageWidth; x++)
			// Plot pixel at (x,y) using RGB color red.
			easyppm_set(&myImage, x, y, easyppm_rgb(x*y / 255, x*y/255 , x*y/255));

	// Write image to PPM file.
	// Use an online PPM image viewer app to see the image...
	// https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html
	// Or, install an image editor such as the free GNU Gimp program.
	easyppm_write(&myImage, "test_image4.ppm");

	// Deallocate (release) memory used to store the image data.
	easyppm_destroy(&myImage);

	// Return error code of 0 to operating system to signal successful exit.
	return 0;
}

#include "Lighting.h"
#include <iostream>
#include <cmath>
using namespace std;

int main() {

	Rgb ambientIntensity(0.3, 0.3, 0.3);
	Rgb ambientMaterial(0.5, 0.5, 0.5);
	
	Tuple lightPoint(0,10,0, 1);
	Rgb   diffuseIntensity(0.5, 0.5, 0.5);
	Rgb   diffuseMaterial(0.8, 0.8, 0.8);
	
	// Camera or eye point used in specular reflection.
	Tuple cameraPoint(-10,10,0, 1);
	
	Rgb   specularIntensity(0.5, 0.5, 0.5);
	Rgb   specularMaterial(0.8, 0.8, 0.8);	
	int   specularExponent = 2;
	
    Tuple objectPoint(0,0,0, 1);
	Tuple objectNormal(0,1,0);
	
	// Compute amount of ambient reflectance from this material.
	cout << "------- Ambient Reflectance -------" << endl;
	Rgb ambient = lightAmbient( ambientMaterial, ambientIntensity );
	cout << "Ambient Light: " << ambient << endl << endl;

	// Compute amount of diffuse reflectance from this material.
	cout << "------- Diffuse Reflectance -------" << endl << endl;
	Rgb diffuse = lightDiffuse(diffuseMaterial, objectPoint, objectNormal, diffuseIntensity, lightPoint );
	cout << "Diffuse Light: " << diffuse << endl;
			
	// Compute amount of specular reflectance from this material.
	cout << "------- Specular Reflectance -------" << endl << endl;
	Rgb specular = lightSpecular(specularMaterial, objectPoint, objectNormal, specularIntensity, lightPoint, cameraPoint, specularExponent );
	cout << "Specular Light: " << specular << endl;

	// Total amount of light reflected from material at objectPoint is the sum of ambient, diffuse, and specular reflectances.
	cout << "------- Total Reflectance -------" << endl << endl;
	Rgb total = ambient + diffuse + specular;
	cout << "Total reflectance: " << total << endl;
	
	// Plot pixel using RGB values in range 0-255
	cout << "Pixel RGB is " << (total.getR() * 255) << ", " << (total.getG() * 255) << ", " << (total.getB() * 255) << endl;
	
	return 0;
}
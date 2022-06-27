#ifndef WAVEMOTION_H
#define WAVEMOTION_H
#include <GLFW/glfw3.h>
#include <linmath.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "globals.h"
#define _USE_MATH_DEFINES
using namespace std;

struct particle
{
	float centerX;
	float centerY;
	float centerZ;
	float radius;
};


// IDEA: TRY MAKING 3D, add z dimension
int waveMotion(float wavelength, float amplitude, float frequency);

#endif
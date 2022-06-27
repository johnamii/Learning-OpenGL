#ifndef POLYRYTHM_H
#define POLYRYTHM_H

#include <GLFW/glfw3.h>
#include <linmath.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <list>
#include "globals.h"
#define _USE_MATH_DEFINES
using namespace std;

// Declaring structures

struct coord
{
	coord(){
		x = 0.0f;
		y = 0.0f;
	}
	coord(float xx, float yy) {
		x = xx;
		y = yy;
	}

	float x;
	float y;
};

struct vector
{
	vector() {}
	vector(coord c, coord t, float r) {
		center = c;
		tip = t;
		rad = r;
	}
	coord center;
	coord tip;
	float rad;
};

// Drawing Functions

void calculateTip(vector& src, float timer);

void drawCircle(vector src, float r, float g, float b);

void drawVector(vector& src, coord base, float color, float counter, float speed);

// TODO: add beats / timed color change, add sound for beat

int polyrythm(int vecCount, int bpm);

#endif
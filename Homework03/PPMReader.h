#pragma once
#include <stdio.h>  
#include <stdlib.h>

typedef struct {
	unsigned char red, green, blue;
} PPMPixel;

typedef struct {
	int x, y;
	PPMPixel *data;
} PPMImage;

#define CREATOR "RPFELGUEIRAS"
#define RGB_COMPONENT_COLOR 255

PPMImage *readPPM(const char *filename);
void writePPM(const char *filename, PPMImage *img);
unsigned char *PixelData(const PPMImage *input);
void ToPPMImage(const unsigned char *input, PPMImage *output);
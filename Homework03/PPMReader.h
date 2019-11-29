#pragma once
#include <stdio.h>  
#include <stdlib.h>

void ReadPPM(const char* file_path, int* width, int* height, char* pixels);
void WritePPM(const char* file_path, const int width, const int height, const int color, const char* pixels);
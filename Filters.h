/** @file */

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#include "Image_loader.h"

//upper pass  sharpen
//lower pass  blur
//median	  denoise
//min and max filters

void box_blur(BMPImageInfo** image);

void sharpen_f(BMPImageInfo** image);

void avg_f(BMPImageInfo** image);

void filtering(BMPImageInfo** image, int kernel[3][3], int normalizing_factor);

int find_maximum(BMPImageInfo** image, int x, int y, char color);

void maximum_filtering(BMPImageInfo** image);

void minimum_filtering(BMPImageInfo** image);

int find_minimum(BMPImageInfo** image, int x, int y, char color);

void median_filtering(BMPImageInfo** image);

int averaging(BMPImageInfo** image, int x, int y, char color);

void average_filtering(BMPImageInfo** image);

int find_median(BMPImageInfo* image, int x, int y, char color);

int clipping(int pixel);

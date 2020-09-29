#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <crtdbg.h>

#include "Image_loader.h"

//upper pass  sharpen
//lower pass  blur
//median	  denoise
//min and max filters

typedef struct Kernel {
	int filter[3][3];
	float normalizing;
}Kernel;

void box_blur(BMPImageInfo** image);

void filtering(BMPImageInfo** image, int kernel[3][3]);

int clipping(int pixel);

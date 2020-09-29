#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "Image_loader.h"

//upper pass  sharpen
//lower pass  blur
//median	  denoise
//min and max filters



BMPImageInfo* upperPass(BMPImageInfo* image);

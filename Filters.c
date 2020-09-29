#include <stdlib.h>
#include <stdio.h>

#include "Filters.h"
#include "Image_loader.h"

BMPImageInfo* upperPass(BMPImageInfo* image)
{
	BMPImageInfo* new_image = malloc(sizeof(BMPImageInfo));

	new_image->header = image->header;
	new_image->pixels= malloc((new_image->header.height_px) * sizeof(Pixel*));
	for (int i = 0; i < new_image->header.height_px; i++) 
	{
		new_image->pixels[i] = malloc((new_image->header.width_px) * sizeof(Pixel));
	}

	

	

}




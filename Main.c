#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>


#include "Image_loader.h"
#include "Filters.h"

void print_help()
{
	puts("Basically PS\n");
	puts("Possible options:");
	puts("--img <path> : Path to image to be performed operation on.");
	puts("--boxblur : Performs box blur algorithm on image.");
	puts("--sharpen : Sharpens an image.");
	puts("--avg :");
	puts("--min : ");
	puts("--max : ");
	puts("--max : ");
	puts("--median : ");
}

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		print_help();
		return 0;
	}

	if (argc == 3)
	{
		for (int i = 0; i < 2; i++)
		{
			strtok
		}
	}
		

	
	BMPImageInfo* image = read_image("Landscape2.bmp");
	
	//wypisaæ listê filtrów i wybraæ
	box_blur(&image);
	write_image("upperpass.bmp", image);
	
	free_image(&image);
	

	_CrtDumpMemoryLeaks();

	return 0;
}

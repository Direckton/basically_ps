#include <stdio.h>
#include <stdlib.h>

#include "Image_loader.h"



int readFile()
{
	BMPImageInfo *image=malloc(sizeof(*image));
	if (image == NULL)
	{
		printf("Memory allocation failed");
		return NULL;
	}

	FILE* stream;

	fopen_s(&stream, "test.bmp", "rb");
	if (stream == NULL) {
		printf("Error: the file could not be opened");
		return 3;
	}
	fread(&image->header, sizeof(image->header), 1, stream);
	
	image->data = malloc(sizeof(*image->data)*image->header.image_size_bytes);

	fclose(stream);
}


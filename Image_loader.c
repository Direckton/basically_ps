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
	int imageData=fread(&image->header, sizeof(image->header), 1, stream);
	
	image->data = malloc(sizeof(*image->data)*image->header.image_size_bytes);

	imageData = fread(image->data,image->header.image_size_bytes, 1, stream);

	return image;

}

bool writeFile()
{
	BMPImageInfo *image=readFile();

	FILE* stream;

	fopen_s(&stream, "copy of test.bmp", "wb");
	if (stream == NULL) {
		printf("Error: the file could not be opened");
		return 3;
	}

	fwrite(&image->header, sizeof(image->header), 1, stream);
	fwrite(&image->data, image->header.image_size_bytes, 1, stream);

	return true;
}


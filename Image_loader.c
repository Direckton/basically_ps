#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Image_loader.h"



int readFile(FILE* stream, char **error)
{
	BMPImageInfo *image=malloc(sizeof(*image));
	if (!check(image!=NULL,error,"Not enough memory!"));
	{
		return NULL;
	}
	rewind(stream);

	int imageData=fread(&image->header, sizeof(image->header), 1, stream);
	if (!check(imageData==1, error, "Cannot read header!"));
	{
		return NULL;
	}
	


	image->data = malloc(sizeof(*image->data)*image->header.image_size_bytes);

	imageData = fread(image->data,image->header.image_size_bytes, 1, stream);

	return image;

}

bool writeFile()
{
	BMPImageInfo *image=readFile(const char fileName, char** error);

	FILE* stream;

	fopen_s(&stream, "copy of test.bmp", "wb");
	if (stream == NULL) {
		printf("Error: the file could not be opened");
		return 3;
	}

	fwrite(&image->header, sizeof(image->header), 1, stream);
	fwrite(image->data, image->header.image_size_bytes, 1, stream);

	return true;
}

bool check(bool condition, char** error, const char* errorMessage)
{
	bool valid = true;
	if (!condition)
	{
		valid = false;
		if (error == NULL)
		{
			*error = stringDuplicate(errorMessage);
		}
	}
	return valid;
}

char *stringDuplicate(const char *string)
{
	char* copy = malloc(sizeof(*copy) * (strlen(string) + 1));
	if (copy == NULL)
	{
		return "Not enough memory for error message";
	}
	strcpy(copy, string);
	
	return copy;
}

FILE* openFile(const char* fileName, const char* mode)
{
	FILE* stream = fopen_s(&stream, fileName, mode);
	if (stream == NULL)
	{
		fprintf(stderr, "Could not open the file %s!",fileName);

		exit(EXIT_FAILURE);
	}

	return stream;
}

bool checkHeader(BMPHeaderInfo* headerInfo, FILE* stream)
{

}
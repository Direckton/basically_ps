#include <stdio.h>
#include <stdlib.h>

#include "Image_loader.h"


int readFile()
{
	BMPHeaderInfo bmpFileInfo;

	FILE* stream;

	fopen_s(&stream, "test.bmp", "rb");
	if (stream == NULL) {
		printf("Error: the file could not be opened");
		return 3;
	}
	fread(&bmpFileInfo, sizeof(BMPHeaderInfo), 1, stream);
	

	fclose(stream);
}
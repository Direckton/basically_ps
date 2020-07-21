#include <stdio.h>
#include <stdlib.h>

#include "Image_loader.h"

void open_bmp_file(char FileName)
{
	FILE* bitmap = fopen(FileName, "rb");
	if (bitmap == NULL)
	{
		printf("Error has occured: no file to read, check if the file exist");
		fclose(bitmap);
		exit(1);
	}

}
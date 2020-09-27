#include <stdio.h>
#include <stdlib.h>

#include "Image_loader.h"

//int readFile()
//{
//	int line[50] = { 0 };
//	FILE* stream;
//
//
//	fopen_s(&stream, "test.bmp", "rb");
//	if (stream == 0)
//		return 3;
//	fread(line, sizeof(int), sizeof(line), stream);
//
//	fclose(stream);
//	for (int i = 0; i < 50; i++)
//	{
//		printf("0x%x\n", line[i]);
//		
//
//	}
//	printf("%p\n", &line[0]);
//}


int main()
{
	char* error = NULL;
	BMPImageInfo *image= read_image("test.bmp", &error);

	return 0;

	printf("all good");
}
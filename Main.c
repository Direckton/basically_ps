#include <stdio.h>
#include <stdlib.h>

#include "Image_loader.h"
#include "Filters.h"

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
	BMPImageInfo* image = read_image("test.bmp");
	write_image("copy_of_test.bmp", image);
	BMPImageInfo* filtered = read_image("copy_of_test.bmp");
	//wypisaæ listê filtrów i wybraæ
	upperPass(image);

	

	return 0;

	printf("all good");
}

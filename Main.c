#include <stdio.h>
#include <stdlib.h>

int readFile()
{
	int line[50] = { 0 };
	FILE* stream;


	fopen_s(&stream, "test.bmp", "rb");
	if (stream == 0)
		return 3;
	fread(line, sizeof(int), sizeof(line), stream);

	fclose(stream);
	for (int i = 0; i < 50; i++)
	{
		printf("0x%x\n", line[i]);
		

	}
	printf("%p\n", &line[0]);
}


int main()
{
	readFile();
	return 0;
}
#include <stdlib.h>
#include <stdio.h>

#include "Functions.h"
#include "Image_loader.h"

int main()
{
	char cum[80];
	FILE* fp;
	fp = fopen("test.txt", "r");	//C://Users//Micha�//Desktop//nauka//Sezon 2//pk//c//basically_ps//basically_ps//basically_ps//
	if (fp == NULL)
	{
		printf("file empty");
		return 1;
	}
	
	fgets(cum, 80, fp);
	printf("%s\n", cum);

	fclose(fp);
	
	FILE* write = fopen("test2.txt", "w");
	if (write == NULL)
	{
		printf("file does not exist");
		return 1;
	}
	fwrite(cum, sizeof(char),80 , write);

	fclose(write);
	return 0;

}
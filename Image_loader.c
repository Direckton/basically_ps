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
	return
		headerInfo->type == BMP_IDENTIFICATOR
		&& headerInfo->offset == BMP_HEADER_SIZE
		&& headerInfo->dib_header_size == DIB_HEADER_SIZE
		&& headerInfo->num_planes == NUM_PLANE
		&& headerInfo->compression == COMMPRESSION
		&& headerInfo->num_colors == NUM_COLORS
		&& headerInfo->important_colors == IMPORTANT_COLORS
		&& headerInfo->bits_per_pixel == BITS_PER_PIXEL
		&& headerInfo->size == getFileSize(stream)
		&& headerInfo->image_size_bytes == get_image_size_in_bytes(stream);

}

long get_file_size(FILE* stream)
{
	long currentPosition = ftell(stream);
	if (currentPosition == -1)
		return -1;
	
	if (fseek(stream, 0, SEEK_END) != 0)
		return -2;

	long fileSize = ftell(stream);
	if (fileSize == -1)
		return -3;

	if (fseek(stream, currentPosition, SEEK_SET) != 0)
		return -4;

	return fileSize;
}

int get_image_size_in_bytes(BMPHeaderInfo* bmpHeader)
{
	return get_image_row_size_bytes(bmpHeader) * bmpHeader->height_px;
}

int get_image_row_size_bytes(BMPHeaderInfo* bmpHeader)
{
	int bytes_per_row_without_padding = bmpHeader->width_px * get_bytes_per_pixel(bmpHeader);
	return bytes_per_row_without_padding + get_padding(bmpHeader);
}

int get_bytes_per_pixel(BMPHeaderInfo* bmpHeader)
{
	return bmpHeader->bits_per_pixel / BITS_PER_BYTE;
}

int get_padding(BMPHeaderInfo* bmpHeader)
{
	return (4 - (bmpHeader->width_px * _get_bytes_per_pixel(bmpHeader)) % 4) % 4;
}


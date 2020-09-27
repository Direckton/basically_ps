#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Image_loader.h"




BMPImageInfo *read_bmp(FILE* stream, char **error)
{
	//Allocate memory for structure
	BMPImageInfo *image=malloc(sizeof(*image));
	if (!check(image!=NULL, error, "Not enough memory!"));
	{
		return NULL;
	}
	//Set file position to the beginning
	rewind(stream);
	//Read header
	int imageData=fread(&image->header, sizeof(image->header), 1, stream);
	if (!check(imageData==1, error, "Cannot read header!"));
	{
		return NULL;
	}
	//Check header
	bool valid_headder = check_header(&image->header, stream);
	if (!check(valid_headder, error, "Invalid BMP file!"))
	{
		return NULL;
	}
	//Allocate memory for image data
	image->data = malloc(sizeof(*image->data)*image->header.image_size_bytes);
	if(!check(image->data != NULL,error,"Not enough memory!"))
	{
		return NULL;
	}
	//Read image data
	imageData = fread(image->data,image->header.image_size_bytes, 1, stream);
	if(!check(imageData == 1, error, "Cannot read image!"))
	{
		return NULL;
	}

	return image;

}

bool write_bmp(FILE *stream, BMPImageInfo *image, char **error)
{
	rewind(stream);
	int image_data = fwrite(&image->header, sizeof(image->header), 1, stream);
	if (!check(image_data == 1, error, "Cannot write header!"))
	{
		return false;
	}
	
	image_data = fwrite(image->data, image->header.image_size_bytes, 1, stream);
	if (!check(image_data == 1, error, "Cannot write image!"))
	{
		return false;
	}

	return true;
}

bool check(bool condition, char** error, const char* error_message)
{
	bool valid = true;
	if (!condition)
	{
		valid = false;
		if (*error == NULL)
		{
			*error = string_duplicate(error_message);
		}
	}
	return valid;
}


char *string_duplicate(const char *string)
{
	char* copy = malloc(sizeof(*copy) * (strlen(string) + 1));
	if (copy == NULL)
	{
		return "Not enough memory for error message";
	}
	strcpy_s(copy,sizeof(copy), string);
	
	return copy;
}

FILE* open_file(const char* fileName, const char* mode)
{
	FILE *stream = fopen_s(&stream, fileName, mode);
	
	/*if (stream == NULL)
	{
		fprintf(stderr, "Could not open the file %s!",fileName);

		exit(EXIT_FAILURE);
	}*/

	return stream;
}

bool check_header(BMPHeaderInfo* headerInfo, FILE* stream)
{
	if (
		headerInfo->type == BMP_IDENTIFICATOR
		&& headerInfo->offset == BMP_HEADER_SIZE
		&& headerInfo->dib_header_size == DIB_HEADER_SIZE
		&& headerInfo->num_planes == NUM_PLANE
		&& headerInfo->compression == COMMPRESSION
		&& headerInfo->num_colors == NUM_COLORS
		&& headerInfo->important_colors == IMPORTANT_COLORS
		&& headerInfo->bits_per_pixel == BITS_PER_PIXEL
		&& headerInfo->size == get_file_size(stream)
		&& headerInfo->image_size_bytes == get_image_size_in_bytes(stream)
		)
		return true;
	else
		return false;
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
	return (4 - (bmpHeader->width_px * get_bytes_per_pixel(bmpHeader)) % 4) % 4;
}


BMPImageInfo* read_image(const char* file_name, char **error)
{
	FILE* pInput = open_file(file_name, "rb");

	BMPImageInfo* image = read_bmp(pInput, error);
	if (*error != NULL)
	{
		handle_error(error, pInput, image);
	}
	fclose(pInput);

	return image;
}

void handle_error(char **error, FILE *stream, BMPImageInfo *image)
{
	fprintf(stderr, "ERROR: %s\n", *error);
	free_memory(stream, image, error);

	exit(EXIT_FAILURE);
}

void free_memory(FILE* stream, BMPImageInfo* image, char** error)
{
	if (stream != NULL)
	{
		fclose(stream);
	}
	free_bmp(image);
	free(*error);
}

void free_bmp(BMPImageInfo* image)
{
	free(image->data);
	free(image);
	image = 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Image_loader.h"



BMPImageInfo *read_bmp(FILE* stream, char **error)
{
	//Allocate memory for structure
	BMPImageInfo *image=malloc(sizeof(*image));
	if (!image)
	{
		add_error(error, "Not enough memory!");
		return NULL;
	}
	
	//Set file position to the beginning
	rewind(stream);
	
	//Read header
	int imageData=fread(&image->header, sizeof(image->header), 1, stream);
	if (imageData != 1)
	{
		add_error(error, "Not enough memory for header!");
		return NULL;
	}
	image->header.image_size_bytes = image->header.size - 54;
	//Check header
	bool valid_header = check_header(&image->header, stream);
	if (!valid_header)
	{
		add_error(error, "Invalid header!");
		return NULL;
	}

	//Allocate memory for 2D pixel array

	image->pixels = (Pixel**)malloc(image->header.height_px * sizeof(Pixel*));
	if (image->pixels == NULL)
	{
		add_error(error, "Not enough memory for pixel array!");
		return NULL;
	}
	for (int i = 0; i < image->header.height_px; i++)
	{
		image->pixels[i] = (Pixel*)malloc(image->header.width_px * sizeof(Pixel));
		if (image->pixels[i] == NULL)
		{
			add_error(error, "Could not add pixels to array!");
			return NULL;
		}
	}

	rewind(stream);

	fseek(stream, 54, SEEK_SET);

	for (int y = 0; y < image->header.height_px; y++)
	{
		fread(image->pixels[y], sizeof(Pixel), image->header.width_px, stream);
	}

	return image;
}

bool write_bmp(FILE *stream, BMPImageInfo *image, char **error)
{
	rewind(stream);
	int image_data = fwrite(&image->header, sizeof(image->header), 1, stream);
	if (image_data != 1)
	{
		add_error(error, "No header data to write!");
		return false;
	}
	
	for (int y = 0; y < image->header.height_px; y++)
	{
		fwrite(image->pixels[y], sizeof(Pixel), image->header.width_px, stream);
	}

	return true;
}

void add_error(char **error, const char* error_message)
{
	if (*error == NULL || *error == "")
		*error = error_message;
}



FILE* open_file(const char* fileName, const char* mode)
{
	FILE* stream;
	auto err = fopen_s(&stream, fileName, mode);
	
	if (stream == NULL)
	{
		fprintf(stderr, "Could not open the file %s!",fileName);

		exit(EXIT_FAILURE);
	}

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
		&& (headerInfo->image_size_bytes == get_image_size_in_bytes(headerInfo)||headerInfo->image_size_bytes == 0)
		) return true;

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


BMPImageInfo* read_image(const char* file_name)
{
	FILE* pInput = open_file(file_name, "rb");
	char* error = NULL; 

	BMPImageInfo* image = read_bmp(pInput, &error);
	
	if (error)
		handle_error(&error, pInput, image);
	
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
	if (!image)
		return;
	
	free(image->pixels);
	free(image);
	image = 0;
}

void write_image(const char* file_name, BMPImageInfo* image)
{
	FILE* pOutput = open_file(file_name, "wb");
	char* error = NULL;

	if (!write_bmp(pOutput, image, &error))
	{
		handle_error(error, pOutput, image);
	}
	fclose(pOutput);
}

void free_image(BMPImageInfo** image)
{
	if (image == NULL)
		return;

	for (int i = 0; i < (*image)->header.height_px; i++)
	{
		free((*image)->pixels[i]);
	}
	free((*image)->pixels);
	free(*image);
}

#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <stdint.h>			//allows to set integer size
#include <stdbool.h>		//allows use of booleans types
#include <stdio.h>			//allows I/O operations

#define BMP_HEADER_SIZE 54	//defining bmp header size for 54 bytes
#define DIB_HEADER_SIZE 40	//same as above

#define BMP_IDENTIFICATOR   0x4D42
#define NUM_PLANE           0x1
#define COMMPRESSION        0
#define NUM_COLORS          0
#define IMPORTANT_COLORS    0
#define BITS_PER_PIXEL      0x18
#define BITS_PER_BYTE       0x8



#pragma pack(push)			//saving original data aligment
#pragma pack(1)				//settin data aligment to 1 byte

typedef struct {
    uint16_t type;              // Magic identifier: 0x4d42
    uint32_t size;              // File size in bytes
    uint16_t reserved1;         // Not used
    uint16_t reserved2;         // Not used
    uint32_t offset;            // Offset to image data in bytes from beginning of file
    uint32_t dib_header_size;   // DIB Header size in bytes
    int32_t  width_px;          // Width of the image
    int32_t  height_px;         // Height of image
    uint16_t num_planes;        // Number of color planes
    uint16_t bits_per_pixel;    // Bits per pixel
    uint32_t compression;       // Compression type
    uint32_t image_size_bytes;  // Image size in bytes
    int32_t  x_resolution_ppm;  // Pixels per meter
    int32_t  y_resolution_ppm;  // Pixels per meter
    uint32_t num_colors;        // Number of colors
    uint32_t important_colors;  // Important colors
}BMPHeaderInfo;

#pragma pack(pop)           //restore saved data aligment

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
}Pixel;


typedef struct {
    BMPHeaderInfo header;
    //unsigned char* data;
    Pixel** pixels;
}BMPImageInfo;

BMPImageInfo *read_bmp(FILE *stream, char** error);

bool write_bmp(FILE* stream, BMPImageInfo* image, char** error);

FILE* open_file(const char* fileName, const char* mode);

bool check_header(BMPHeaderInfo* headerInfo, FILE* stream);

long get_file_size(FILE* stream);

int get_image_size_in_bytes(BMPHeaderInfo* bmpHeader);

int get_image_row_size_bytes(BMPHeaderInfo* bmpHeader);

int get_bytes_per_pixel(BMPHeaderInfo* bmpHeader);

int get_padding(BMPHeaderInfo* bmpHeader);

BMPImageInfo* read_image(const char* file_name);

void handle_error(char** error, FILE* stream, BMPImageInfo* image);

void free_memory(FILE* stream, BMPImageInfo* image, char** error);

void free_bmp(BMPImageInfo* image);

void write_image(const char* file_name, BMPImageInfo* image);

void free_image(BMPImageInfo** image);

void add_error(char** error, const char* error_message);

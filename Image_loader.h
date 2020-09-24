#pragma once

#include <stdint.h>			//allows to set integer size
#include <stdbool.h>		//allows use of booleans types
#include <stdio.h>			//allows I/O operations

#define BMP_HEADER_SIZE 54	//defining bmp header size for 54 bytes
#define DIB_HEADER_SIZE 40	//same as above

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
    BMPHeaderInfo header;
    unsigned char* data;
}BMPImageInfo;


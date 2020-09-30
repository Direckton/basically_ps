/** @file */

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#include "Image_loader.h"

//upper pass  sharpen
//lower pass  blur
//median	  denoise
//min and max filters


/**@return Function passes kernel and normalizing factor needed to achieve blured image
@param image pointer to structure containing bmp image*/
void box_blur(BMPImageInfo** image);

/**Function passes kernel and normalizing factor needed to achieve sharpened image
@param image pointer to structure containing bmp image*/
void sharpen_f(BMPImageInfo** image);

/**Function passes pointer on find_maximum function to linear_filtering function
@param image pointer to structure containing bmp image*/
void maximum_filter(BMPImageInfo** image);

/**Function passes values neccessery for calculations and overwtires calculated pixel values to stucture containing image
@param image pointer to structure containing bmp image
@param kernel array conating filtering kernel
@param normalizing_value array normalizing factor*/
void kernel_filtering(BMPImageInfo** image, int kernel[3][3], int normalizing_factor);

/**Function finds maximum value from an array of pixels around examined pixel and assings it to this pixel
@param image pointer to structure containing bmp image
@param x horizontal coordinate of examined pixel
@param y vertical coordinate of examined pixel
@param color character containing coresponding RGB letter*/
int find_maximum(BMPImageInfo** image, int x, int y, char color);

/**Function passes values neccessery for calculations and overwtires calculated pixel values to stucture containing image
@param image pointer to structure containing bmp image
@param *foo pointer to the function*/
void linear_filtering(BMPImageInfo** image, int(*foo)(BMPImageInfo*, int, int, char));

/**Function passes pointer on find_minimum function to linear_filtering function
@param image pointer to structure containing bmp image*/
void minimum_filter(BMPImageInfo** image);

/**Function finds minimum value from an array of pixels around examined pixel and assings it to this pixel
@param image pointer to structure containing bmp image
@param x horizontal coordinate of examined pixel
@param y vertical coordinate of examined pixel
@param color character containing coresponding RGB letter*/
int find_minimum(BMPImageInfo** image, int x, int y, char color);

/**Function passes pointer on find_median function to linear_filtering function
@param image pointer to structure containing bmp image*/
void median_filter(BMPImageInfo** image);
/**Function finds average value from an array of pixels around examined pixel and assings it to this pixel
@param image pointer to structure containing bmp image
@param x horizontal coordinate of examined pixel
@param y vertical coordinate of examined pixel
@param color character containing coresponding RGB letter*/
int find_average(BMPImageInfo** image, int x, int y, char color);

/**Function passes pointer on find_average function to linear_filtering function
@param image pointer to structure containing bmp image*/
void average_filter(BMPImageInfo** image);

/**Function finds median from a sorted array of pixels around examined pixel and assings it to this pixel
@param image pointer to structure containing bmp image
@param x horizontal coordinate of examined pixel
@param y vertical coordinate of examined pixel
@param color character containing coresponding RGB letter*/
int find_median(BMPImageInfo* image, int x, int y, char color);

/**Function checks if slected pixel is at the end of row or column and moves it 
,chooses pixel.color structure to write in
@param image pointer to structure containing bmp image
@param x horizontal coordinate of examined pixel
@param y vertical coordinate of examined pixel
@param color character containing coresponding RGB letter*/
int check_border(BMPImageInfo* image, int x, int y, char color);

/**Function clips returned value to maximum or minimum value of 8 bit color
@param pixel integer containing pixel value*/
int clipping(int pixel);

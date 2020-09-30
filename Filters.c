/** @file */


#include <stdlib.h>
#include <stdio.h>

#include "Filters.h"
#include "Image_loader.h"

void box_blur(BMPImageInfo** image)
{
	int upper_pass_kernel[3][3]= {	{1,1,1},
									{1,1,1},
									{1,1,1}};
	int normalizing_factor = 9;
	filtering(image, upper_pass_kernel, normalizing_factor);
}

void sharpen_f(BMPImageInfo** image)
{
	int upper_pass_kernel[3][3] = { {0,-1,0},
									{-1,5,-1},
									{0,-1,0} };
	int normalizing_factor = 1;
	filtering(image, upper_pass_kernel,normalizing_factor);
}


void filtering(BMPImageInfo** image, int kernel[3][3], int normalizing_factor)
{	
	int midPixB = 0;
	int midPixG = 0;
	int midPixR = 0;
	
	
	for (int y = 0; y < (*image)->header.height_px; y++) 
	{
		for (int x = 0; x < (*image)->header.width_px; x++) 
		{
			//sum for blue
			midPixB = newPix(*image, x, y, 'b', kernel, normalizing_factor);
			//sum for green
			midPixG = newPix(*image, x, y, 'g', kernel, normalizing_factor);
			//sum for red
			midPixR = newPix(*image, x, y, 'r', kernel, normalizing_factor);

			// makes sure the pixels are in the range of 0-255
			midPixB = clipping(midPixB);
			midPixG = clipping(midPixG);
			midPixR = clipping(midPixR);

			// assigns the values of newly calculated pixel to target pixel
			(*image)->pixels[y][x].blue = midPixB;
			(*image)->pixels[y][x].green = midPixG;
			(*image)->pixels[y][x].red = midPixR;
		}
	}

}

int find_maximum(BMPImageInfo** image, int x, int y, char color)
{
	int max = 0;
	int array[3][3];
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			array[i + 1][y + 1] = check_border(image, x + i, y + j, color);
			if (array[i + 1][y + 1] > max)
				max = array[i + 1][y + 1];
		}
	}

	return max;
}


void maximum_filtering(BMPImageInfo** image)
{
	int midPixB = 0;
	int midPixG = 0;
	int midPixR = 0;


	for (int y = 0; y < (*image)->header.height_px; y++)
	{
		for (int x = 0; x < (*image)->header.width_px; x++)
		{
			//sum for blue
			midPixB = find_maximum(*image, x, y, 'b');
			//sum for green
			midPixG = find_maximum(*image, x, y, 'g');
			//sum for red
			midPixR = find_maximum(*image, x, y, 'r');

			// makes sure the pixels are in the range of 0-255
			midPixB = clipping(midPixB);
			midPixG = clipping(midPixG);
			midPixR = clipping(midPixR);

			// assigns the values of newly calculated pixel to target pixel
			(*image)->pixels[y][x].blue = midPixB;
			(*image)->pixels[y][x].green = midPixG;
			(*image)->pixels[y][x].red = midPixR;
		}
	}

}

void minimum_filtering(BMPImageInfo** image)
{
	int midPixB = 0;
	int midPixG = 0;
	int midPixR = 0;


	for (int y = 0; y < (*image)->header.height_px; y++)
	{
		for (int x = 0; x < (*image)->header.width_px; x++)
		{
			//sum for blue
			midPixB = find_minimum(*image, x, y, 'b');
			//sum for green
			midPixG = find_minimum(*image, x, y, 'g');
			//sum for red
			midPixR = find_minimum(*image, x, y, 'r');

			// makes sure the pixels are in the range of 0-255
			midPixB = clipping(midPixB);
			midPixG = clipping(midPixG);
			midPixR = clipping(midPixR);

			// assigns the values of newly calculated pixel to target pixel
			(*image)->pixels[y][x].blue = midPixB;
			(*image)->pixels[y][x].green = midPixG;
			(*image)->pixels[y][x].red = midPixR;
		}
	}

}

int find_minimum(BMPImageInfo** image, int x, int y, char color)
{
	int min = 256;
	int array[3][3];
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			array[i+1][y+1] = check_border(image, x + i, y + j, color);
			if (array[i + 1][y + 1] < min)
				min = array[i + 1][y + 1];
		}
	}

	return min;
}

void median_filtering(BMPImageInfo** image)
{
	int midPixB = 0;
	int midPixG = 0;
	int midPixR = 0;


	for (int y = 0; y < (*image)->header.height_px; y++)
	{
		for (int x = 0; x < (*image)->header.width_px; x++)
		{
			//sum for blue
			midPixB = find_median(*image, x, y, 'b');
			//sum for green
			midPixG = find_median(*image, x, y, 'g');
			//sum for red
			midPixR = find_median(*image, x, y, 'r');

			// makes sure the pixels are in the range of 0-255
			midPixB = clipping(midPixB);
			midPixG = clipping(midPixG);
			midPixR = clipping(midPixR);

			// assigns the values of newly calculated pixel to target pixel
			(*image)->pixels[y][x].blue = midPixB;
			(*image)->pixels[y][x].green = midPixG;
			(*image)->pixels[y][x].red = midPixR;
		}
	}

}

int averaging(BMPImageInfo** image, int x, int y, char color)
{

	int sum=0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			sum += check_border(image, x + i, y + j, color);
		}
	}
	float average = sum / 9;
	floor(average);
	return average;
}

void average_filtering(BMPImageInfo **image)
{

	int midPixB = 0;
	int midPixG = 0;
	int midPixR = 0;


	for (int y = 0; y < (*image)->header.height_px; y++)
	{
		for (int x = 0; x < (*image)->header.width_px; x++)
		{
			//sum for blue
			midPixB = averaging(*image, x, y, 'b');
			//sum for green
			midPixG = averaging(*image, x, y, 'g');
			//sum for red
			midPixR = averaging(*image, x, y, 'r');

			// makes sure the pixels are in the range of 0-255
			midPixB = clipping(midPixB);
			midPixG = clipping(midPixG);
			midPixR = clipping(midPixR);

			// assigns the values of newly calculated pixel to target pixel
			(*image)->pixels[y][x].blue = midPixB;
			(*image)->pixels[y][x].green = midPixG;
			(*image)->pixels[y][x].red = midPixR;
		}
	}

}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int find_median(BMPImageInfo* image, int x, int y, char color)
{
	int array[3][3];

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			array[i+1][j+1] = check_border(image, x + i, y + j, color);
		}
	}
	
	int swap = 0;
	int temp;
	int sorted[9];
	int k = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sorted[k] = array[i][j];
			k++;
		}
	}

	qsort(sorted, 9, sizeof(int), cmpfunc);
	
	return sorted[4];
}

int newPix(BMPImageInfo* image, int x, int y, char color, int kernel[3][3], int normalizing_factor) {
	int midPix;
	midPix = check_border(image, x + 1, y + 1, color) * kernel[2][2];
	midPix += check_border(image, x - 1, y + 1, color) * kernel[2][0];
	midPix += check_border(image, x, y + 1, color) * kernel[2][1];
	midPix += check_border(image, x + 1, y - 1, color) * kernel[0][2];
	midPix += check_border(image, x - 1, y - 1, color) * kernel[0][0];
	midPix += check_border(image, x, y - 1, color) * kernel[0][1];
	midPix += check_border(image, x - 1, y, color) * kernel[1][0];
	midPix += check_border(image, x + 1, y, color) * kernel[1][2];
	midPix += check_border(image, x, y, color) * kernel[1][1];
	return (midPix / normalizing_factor);
}

int check_border(BMPImageInfo* image, int x, int y, char color) 
{
	if (x < 0) {
		x++; // shift right
	}
	if (x >= image->header.width_px) {
		x--; //shift left
	}
	if (y < 0) {
		y++; //shift down
	}
	if (y >= image->header.height_px) {
		y--; //shift up
	}
	if (color == 'b') {
		return image->pixels[y][x].blue;
	}
	else if (color == 'g') {
		return image->pixels[y][x].green;
	}
	else if (color == 'r') {
		return image->pixels[y][x].red;
	}
}

int clipping(int pixel)
{
	if (pixel > 255)
		return 255;
	else if (pixel < 0)
		return 0;
	return pixel;
}


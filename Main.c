/** @file */


#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#include "Image_loader.h"
#include "Filters.h"
#include "argparse.h"


int main(int argc, const char** argv)
{
	const char* image_path = NULL;
	const char* output_image_name = NULL;
	int boxblur = 0;
	int sharpen = 0;
	int avg = 0;
	int min = 0;
	int max = 0;
	int median = 0;

	const char* const usage[] = {
		"basically_ps [options] [[--] args]",
		"basically_ps [options]",
		NULL,
	};

	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_GROUP("Basic options"),
		OPT_STRING('p', "img", &image_path, "path to image"),
		OPT_STRING('o', "out", &output_image_name, "name for processed output image"),
		OPT_BOOLEAN('b', "boxblur", &boxblur, "box blurs an image"),
		OPT_BOOLEAN('s', "sharpen", &sharpen, "sharpens an image"),
		OPT_BOOLEAN('a', "avg", &avg, "averages pixel with values around that pixel? XD"),
		OPT_BOOLEAN('n', "min", &min, ""),
		OPT_BOOLEAN('x', "max", &max, ""),
		OPT_BOOLEAN('m', "median", &median, ""),
		OPT_END()
	};

	struct argparse argparse;
	argparse_init(&argparse, options, usage, 0);
	argparse_describe(&argparse, "\nThis is basically minified ripoff of popular image altering program call Photoshop.\
									I don't know maybe you've heard about it. It's kinda trash that's why you are using\
									this program that never lets you down.",
								 "\Nothing to see here just quitting.");
	argc = argparse_parse(&argparse, argc, argv);

	if (image_path == NULL)
	{
		puts("Path cannot be empty!");
		return -1;
	}

	printf("Loading image from: %s\n", image_path);
	BMPImageInfo* image = read_image(image_path);
	if (image == NULL)
	{
		puts("Could not load image! Quitting.");
		return -1;
	}
	
	if (boxblur != 0)
	{
		puts(" Running box blur!");
		box_blur(&image);
	}
	else if (sharpen != 0)
	{
		puts("Sharpening an image!");
		sharpen_f(&image);
		
	}
	else if (avg != 0)
	{
		puts("Averaging an image!");
		average_filtering(&image);
		
	}
	else if (min != 0)
	{
		puts("Just min");
		minimum_filtering(&image);
	}
	else if (max != 0)
	{
		puts("Just max");
		maximum_filtering(&image);
	}
	else if (median != 0)
	{
		puts("Median who?");
		median_filtering(&image);
		
	}
		
	printf("Saving image as: %s", output_image_name);
	write_image(output_image_name, image);
	free_image(&image);
	
	#ifdef _DEBUG
		_CrtDumpMemoryLeaks();
	#endif
	
	return 0;
}

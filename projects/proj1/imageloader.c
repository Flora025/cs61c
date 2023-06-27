/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

// Opens a .ppm P3 image file, and constructs an Image object.
// You may find the function fscanf useful.
// Make sure that you close the file with fclose before returning.
Image *readData(char *filename)
{
	// YOUR CODE HERE
	// open a ppm file
	FILE *fp = fopen(filename, "r");

	// read headers
	int scale, width, height;
	char format[2];
	fscanf(fp, "%s %d %d %d", format, &width, &height, &scale);

	// create an img object
	// create a dynamic arr to save colors; update rows and cols
	Image *img = malloc(sizeof(Color) + sizeof(uint32_t) * 2);
	img->rows = height;
	img->cols = width;
	img->image = malloc(height * width * sizeof(Color *));

	// read colors
	for (int i = 0; i < width * height; i++)
	{
		Color *newColor = malloc(sizeof(Color));
		uint8_t R, G, B;
		// scan the next group of R G B
		fscanf(fp, "%hhu %hhu %hhu", &R, &G, &B);
		newColor->R = R;
		newColor->G = G;
		newColor->B = B;
		// add the color to IMAGE arr of colors
		img->image[i] = newColor;
	}

	// close the file
	fclose(fp);

	return img;
}

// Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	// YOUR CODE HERE
	// print the RGB val of each COLOR in the IMAGE arr,
	// according to the COLS and ROWS
	printf("P3\n");
	printf("%d %d\n", image->cols, image->rows);
	printf("255\n");

	int count = 0;
	for (int i = 0; i < image->cols * image->rows; i++)
	{
		Color *curColor;
		curColor = image->image[i];

		// add space btw inline rgb
		if (count != 0)
		{
			printf("   ");
		}

		// print (R, G, B)
		// %3u enables自动补位
		printf("%3u %3u %3u", curColor->R, curColor->G, curColor->B);

		// update \n control param
		count++;
		if (count == image->cols)
		{
			printf("\n");
			count = 0;
		}
	}
}

// Frees an image
void freeImage(Image *image)
{
	// YOUR CODE HERE
	// free the memory of each color
	for (int i = 0; i < image->cols * image->rows; i++)
	{
		free(image->image[i]);
	}

	// free the img struct
	free(image->image);
}
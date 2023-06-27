/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

// Determines what color the cell at the given row/col should be.
// This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	// YOUR CODE HERE

	// calc arr pos
	int i = row * image->cols + col;

	// init new color
	Color *curColor = image->image[i];

	// eval the bit representation of the pixel
	Color *res = malloc(sizeof(Color));
	if (curColor->B & 0x01)
	{
		// lastDigit == 1
		res->R = (uint8_t)255, res->G = (uint8_t)255, res->B = (uint8_t)255;
	}
	else
	{
		// lastDigit == 0
		res->R = (uint8_t)0, res->G = (uint8_t)0, res->B = (uint8_t)0;
	}

	return res;
}

// Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	// YOUR CODE HERE
	int size = image->cols * image->rows;
	// init decoded img
	Image *decoImg = malloc(sizeof(Image));
	decoImg->image = malloc(size * sizeof(Color *));
	decoImg->cols = image->cols;
	decoImg->rows = image->rows;

	// iterate through all pixels (colors) in image
	// and extract their B values (black or white)
	for (int r = 0; r < image->rows; r++)
	{
		for (int c = 0; c < image->cols; c++)
		{
			decoImg->image[c + r * image->cols] = evaluateOnePixel(image, r, c);
		}
	}

	return decoImg;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image,
where each pixel is black if the LSB of the B channel is 0,
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	// YOUR CODE HERE

	if (argc != 2)
	{
		printf("usage: %s filename\n", argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		exit(-1);
	}

	char *filename = argv[1];
	Image *image = readData(filename);
	image = steganography(image);
	writeData(image);
	freeImage(image);

	return 0;
}

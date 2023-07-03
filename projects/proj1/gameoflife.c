/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "imageloader.h"

// Determines what color the cell at the given row/col should be. This function
// allocates space for a new Color. Note that you will need to read the eight
// neighbors of the cell in question. The grid "wraps", so we treat the top row
// as adjacent to the bottom row and the left column as adjacent to the right
// column.
Color* evaluateOneCell(Image* image, int row, int col, uint32_t rule) {
    // YOUR CODE HERE
    // init new color
    Color* newColor = malloc(sizeof(Color));

    // 1. Scan neighboring cells:
    // if (rule), return live; else return die
    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[] = {1, 1, 1, 0, 0, -1, -1, -1};
    int bits24[24] = {0};

    // 1.1 get the neighbor status *bits24* of cur cell
    for (int i = 0; i < 8; ++i) {
        int curX = (col + dx[i] + image->cols) % image->cols;
        int curY = (row + dy[i] + image->rows) % image->rows;
        int index = curY * image->cols + curX;  // index of curcolor
        Color* curColor = image->image[index];  // current color
        for (int j = 0; j < 8; j++) {
            if (curColor->R & (1 << j))
                bits24[j]++;
            if (curColor->G & (1 << j))
                bits24[j + 8]++;
            if (curColor->B & (1 << j))
                bits24[j + 16]++;
        }
    }

    // 1.2 decide the newColor according to RULE and bits24
    for (int j = 0; j < 8; ++j) {
        Color* c = image->image[row * image->cols + col];  // current color
        int bitOneR = c->R & (1 << j);
        int bitOneG = c->G & (1 << j);
        int bitOneB = c->B & (1 << j);

        int shiftR = bitOneR * 9 + bits24[j];
        int shiftG = bitOneG * 9 + bits24[j + 8];
        int shiftB = bitOneB * 9 + bits24[j + 16];

        if (rule & (1 << shiftR)) {
            newColor->R |= 1 << j;
        } else {
            newColor->R &= ~(1 << j);
        }

        if (rule & (1 << shiftG)) {
            newColor->G |= 1 << j;
        } else {
            newColor->G &= ~(1 << j);
        }
        if (rule & (1 << shiftB)) {
            newColor->B |= 1 << j;
        } else {
            newColor->B &= ~(1 << j);
        }
    }
    return newColor;
}

// The main body of Life; given an image and a rule, computes one iteration of
// the Game of Life. You should be able to copy most of this from
// steganography.c
Image* life(Image* image, uint32_t rule) {
    // YOUR CODE HERE
    int size = image->cols * image->rows;
    // init decoded img
    Image* decoImg = malloc(sizeof(Image));
    decoImg->image = malloc(size * sizeof(Color*));
    decoImg->cols = image->cols;
    decoImg->rows = image->rows;

    // iterate through all pixels (colors) in image
    // and extract their B values (black or white)
    for (int r = 0; r < image->rows; r++) {
        for (int c = 0; c < image->cols; c++) {
            decoImg->image[c + r * image->cols] =
                evaluateOneCell(image, r, c, rule);
        }
    }

    return decoImg;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then
prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this
will be a string. You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you
should exit with code -1. Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start. <- the
course even teaches cv magic lol
*/
int main(int argc, char** argv) {
    // YOUR CODE HERE
    // TODO: compile and run test
    if (argc != 3) {
        printf("usage: %s filename\n", argv[0]);
        printf(
            "filename is an ASCII PPM file (type P3) with maximum value "
            "255.\n");
        exit(-1);
    }

    char* filename = argv[1];
    uint32_t rule = strtol(argv[2], NULL, 16);

    Image* image = readData(filename);
    image = life(image, rule);
    writeData(image);
    freeImage(image);

    return 0;
}

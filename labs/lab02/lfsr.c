#include "lfsr.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lfsr_calculate(uint16_t* reg) {
    /* YOUR CODE HERE */
    // calc new bit
    uint16_t newBit =
        ((((*reg >> 0) & 1) ^ ((*reg >> 2) & 1)) ^ ((*reg >> 3) & 1)) ^
        ((*reg >> 5) & 1);

    // shift 1 bit to right
    *reg = (*reg >> 1);

    // shift in new bit
    uint16_t mask = (1 << 15);
    *reg &= ~mask;
    *reg |= (newBit << 15);

    printf("My number is: %u\n", *reg);
    // Result: Got 65535 numbers before cycling! Congratulations! It works!
}
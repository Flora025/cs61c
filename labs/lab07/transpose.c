#include "transpose.h"

/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int* dst, int* src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}

/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
void transpose_blocking(int n, int blocksize, int* dst, int* src) {
    // YOUR CODE HERE
    int blockN = n / blocksize + 1;
    int lineRemains = n % blocksize;
    for (int blockRow = 0; blockRow < blockN; blockRow++) {
        // limit max row of cur loop if it's the last block
        int blockRowLimit = (blockRow == blockN - 1) ? lineRemains : blocksize;
        for (int blockCol = 0; blockCol < blockN; blockCol++) {
            // limit max col if it's the last block
            int blockColLimit =
                (blockCol == blockN - 1) ? lineRemains : blocksize;
            for (int x = 0; x < blockRowLimit; x++) {
                for (int y = 0; y < blockColLimit; y++) {
                    dst[(blockCol * blocksize + y) * n +
                        (blockRow * blocksize + x)] =
                        src[(blockRow * blocksize + x) * n +
                            (blockCol * blocksize + y)];
                }
            }
        }
    }
}

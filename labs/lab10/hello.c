#include <omp.h>
#include <stdio.h>

// note: gcc linked to the wrong clang (causing openmp failures)
// solution: CC=clang in makefile
int main() {
#pragma omp parallel
    {
        int thread_ID = omp_get_thread_num();
        printf(" hello world %d\n", thread_ID);
    }
}

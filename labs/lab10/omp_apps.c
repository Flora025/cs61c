#include "omp_apps.h"

/* -------------------------------Utilties, Do Not
 * Modify------------------------------*/
double* gen_array(int n) {
    double* array = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
        array[i] = drand48();
    return array;
}

int verify(double* x,
           double* y,
           void (*funct)(double* x, double* y, double* z)) {
    double* z_v_add = (double*)malloc(ARRAY_SIZE * sizeof(double));
    double* z_oracle = (double*)malloc(ARRAY_SIZE * sizeof(double));
    (*funct)(x, y, z_v_add);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        z_oracle[i] = x[i] + y[i];
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (z_oracle[i] != z_v_add[i])
            return 0;
    }
    return 1;
}

/* -------------------------------Vector
 * Addition------------------------------*/
// BEGIN PART 1 EX 2
void v_add_naive(double* x, double* y, double* z) {
// each thread is executing all of the code within the omp parallel block
#pragma omp parallel
    {
        for (int i = 0; i < ARRAY_SIZE; i++)
            z[i] = x[i] + y[i];
    }
}

// Adjacent Method
void v_add_optimized_adjacent(double* x, double* y, double* z) {
// DONE: Modify this function
// Do NOT use the `for` directive here!
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        // # total available threads
        int num_threads = omp_get_num_threads();

        for (int i = thread_id; i < ARRAY_SIZE; i += num_threads) {
            z[i] = x[i] + y[i];
        }
    }
}

// Chunks Method
void v_add_optimized_chunks(double* x, double* y, double* z) {
// DONE: Modify this function
// Do NOT use the `for` directive here!
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        // # total available threads
        int num_threads = omp_get_num_threads();
        int chunk_size = ARRAY_SIZE / num_threads;
        int start = thread_id * chunk_size;
        int end = start + chunk_size;

        for (int i = start; i < end; i++) {
            z[i] = x[i] + y[i];
        }

        // handle the tail cases with the last thread
        if (thread_id == num_threads - 1) {
            // starting from where the body loop ends
            for (int i = end; i < ARRAY_SIZE; i++) {
                z[i] = x[i] + y[i];
            }
        }
    }
}
// END PART 1 EX 2

/* Results:
Optimized adjacent: 1 thread(s) took 0.574246 seconds
Optimized adjacent: 2 thread(s) took 0.708957 seconds
Optimized adjacent: 3 thread(s) took 0.269535 seconds
Optimized adjacent: 4 thread(s) took 0.253366 seconds
Optimized adjacent: 5 thread(s) took 0.267068 seconds
Optimized adjacent: 6 thread(s) took 0.283848 seconds
Optimized adjacent: 7 thread(s) took 0.278229 seconds
Optimized adjacent: 8 thread(s) took 0.334409 seconds
Optimized chunks: 1 thread(s) took 0.540831 seconds
Optimized chunks: 2 thread(s) took 0.267328 seconds
Optimized chunks: 3 thread(s) took 0.192493 seconds
Optimized chunks: 4 thread(s) took 0.146344 seconds
Optimized chunks: 5 thread(s) took 0.124286 seconds
Optimized chunks: 6 thread(s) took 0.109399 seconds
Optimized chunks: 7 thread(s) took 0.141042 seconds
Optimized chunks: 8 thread(s) took 0.133350 seconds
Naive: 1 thread(s) took 0.520647 seconds
Naive: 2 thread(s) took 0.540320 seconds
Naive: 3 thread(s) took 0.563091 seconds
Naive: 4 thread(s) took 0.570182 seconds
Naive: 5 thread(s) took 0.581667 seconds
Naive: 6 thread(s) took 0.610136 seconds
Naive: 7 thread(s) took 0.911880 seconds
Naive: 8 thread(s) took 0.961827 seconds
*/

/* -------------------------------Dot Product------------------------------*/
// BEGIN PART 1 EX 3
double dotp_naive(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < arr_size; i++)
#pragma omp critical
            global_sum += x[i] * y[i];
    }
    return global_sum;
}

// Manual Reduction
double dotp_manual_optimized(double* x, double* y, int arr_size) {
    // DONE: Modify this function
    // Do NOT use the `reduction` directive here!
    double global_sum = 0.0;
#pragma omp parallel
    {
        // for each thread
        double local_sum = 0.0;

#pragma omp for
        for (int i = 0; i < arr_size; i++) {
            local_sum += x[i] * y[i];
        }

#pragma omp critical
        { global_sum += local_sum; }
    }

    return global_sum;
}

// Reduction Keyword
double dotp_reduction_optimized(double* x, double* y, int arr_size) {
    // DONE: Modify this function
    // Please DO use the `reduction` directive here!
    double global_sum = 0.0;
#pragma omp parallel
    {
#pragma omp for reduction(+ : global_sum)
        for (int i = 0; i < arr_size; i++) {
            global_sum += x[i] * y[i];
        }
    }
    return global_sum;
}
// END PART 1 EX 3
/* Results:

Manual Optimized: 1 thread(s) took 1.036692 seconds
Manual Optimized: 2 thread(s) took 0.522414 seconds
Manual Optimized: 3 thread(s) took 0.358876 seconds
Manual Optimized: 4 thread(s) took 0.278275 seconds
Manual Optimized: 5 thread(s) took 0.233082 seconds
Manual Optimized: 6 thread(s) took 0.196178 seconds
Manual Optimized: 7 thread(s) took 0.294464 seconds
Manual Optimized: 8 thread(s) took 0.264450 seconds
Reduction Optimized: 1 thread(s) took 1.028402 seconds
Reduction Optimized: 2 thread(s) took 0.525278 seconds
Reduction Optimized: 3 thread(s) took 0.361390 seconds
Reduction Optimized: 4 thread(s) took 0.272564 seconds
Reduction Optimized: 5 thread(s) took 0.229433 seconds
Reduction Optimized: 6 thread(s) took 0.208741 seconds
Reduction Optimized: 7 thread(s) took 0.239624 seconds
Reduction Optimized: 8 thread(s) took 0.225260 seconds
Naive: 1 thread took 4.131741 seconds

*/

char* compute_dotp(int arr_size) {
    // Generate input vectors
    char *report_buf = (char*)malloc(BUF_SIZE), *pos = report_buf;
    double start_time, run_time;

    double *x = gen_array(arr_size), *y = gen_array(arr_size);
    double serial_result = 0.0, result = 0.0;

    // calculate result serially
    for (int i = 0; i < arr_size; i++) {
        serial_result += x[i] * y[i];
    }

    int num_threads = omp_get_max_threads();
    for (int i = 1; i <= num_threads; i++) {
        omp_set_num_threads(i);
        start_time = omp_get_wtime();
        for (int j = 0; j < REPEAT; j++)
            result = dotp_manual_optimized(x, y, arr_size);
        run_time = omp_get_wtime() - start_time;
        pos += sprintf(pos, "Manual Optimized: %d thread(s) took %f seconds\n",
                       i, run_time);

        // verify result is correct (within some threshold)
        if (fabs(serial_result - result) > 0.001) {
            pos += sprintf(pos, "Incorrect result!\n");
            *pos = '\0';
            return report_buf;
        }
    }

    for (int i = 1; i <= num_threads; i++) {
        omp_set_num_threads(i);
        start_time = omp_get_wtime();

        for (int j = 0; j < REPEAT; j++) {
            result = dotp_reduction_optimized(x, y, arr_size);
        }

        run_time = omp_get_wtime() - start_time;
        pos +=
            sprintf(pos, "Reduction Optimized: %d thread(s) took %f seconds\n",
                    i, run_time);

        // verify result is correct (within some threshold)
        if (fabs(serial_result - result) > 0.001) {
            pos += sprintf(pos, "Incorrect result!\n");
            *pos = '\0';
            return report_buf;
        }
    }

    // Only run this once because it's too slow..
    omp_set_num_threads(1);
    start_time = omp_get_wtime();
    for (int j = 0; j < REPEAT; j++)
        result = dotp_naive(x, y, arr_size);
    run_time = omp_get_wtime() - start_time;

    pos += sprintf(pos, "Naive: %d thread(s) took %f seconds\n", 1, run_time);
    *pos = '\0';
    return report_buf;
}

/* ---------------------Image Processing: Sobel Edge
 * Detector----------------------*/
int sobel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
void sobel_filter(bmp_pixel** src, bmp_pixel** dst, int row, int col) {
    int res = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            bmp_pixel pxl = src[row - 1 + i][col - 1 + j];
            res +=
                ((int)pxl.blue + (int)pxl.green + (int)pxl.red) * sobel[i][j];
        }
    }
    res *= 2;  // scale a little bit so the result image is brighter.
    res = res < 0 ? 0 : (res > 255 ? 255 : res);
    bmp_pixel_init(&dst[row][col], res, res, res);
}

char* image_proc(const char* filename) {
    bmp_img img, img_copy;
    if (bmp_img_read(&img, filename) != 0)
        return 0;

    char* res = (char*)calloc(32, sizeof(char));
    strncat(res, filename, strlen(filename) - 4);
    strcat(res, "_sobel.bmp");

    bmp_img_read(&img_copy, filename);

    unsigned int wid = img.img_header.biWidth;
    unsigned int hgt = img.img_header.biHeight;
    bmp_img_init_df(&img_copy, wid, hgt);

    // To parallelize these for loops, check out scheduling policy:
    // http://jakascorner.com/blog/2016/06/omp-for-scheduling.html and omp
    // collapse directive
    // https://software.intel.com/en-us/articles/openmp-loop-collapse-directive
    for (int i = 1; i < hgt - 1; i++) {
        for (int j = 1; j < wid - 1; j++) {
            sobel_filter(img.img_pixels, img_copy.img_pixels, i, j);
        }
    }
    bmp_img_write(&img_copy, res);
    bmp_img_free(&img_copy);
    bmp_img_free(&img);
    return res;
}
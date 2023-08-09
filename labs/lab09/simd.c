#include "simd.h"
#include <stdio.h>
#include <time.h>
// #include <x86intrin.h>
#include <arm_neon.h>

long long int sum(int vals[NUM_ELEMS]) {
    clock_t start = clock();

    long long int sum = 0;
    for (unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        for (unsigned int i = 0; i < NUM_ELEMS; i++) {
            if (vals[i] >= 128) {
                sum += vals[i];
            }
        }
    }
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return sum;
}

long long int sum_unrolled(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    long long int sum = 0;

    for (unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        for (unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
            if (vals[i] >= 128)
                sum += vals[i];
            if (vals[i + 1] >= 128)
                sum += vals[i + 1];
            if (vals[i + 2] >= 128)
                sum += vals[i + 2];
            if (vals[i + 3] >= 128)
                sum += vals[i + 3];
        }

        // This is what we call the TAIL CASE
        // For when NUM_ELEMS isn't a multiple of 4
        // NONTRIVIAL FACT: NUM_ELEMS / 4 * 4 is the largest multiple of 4 less
        // than NUM_ELEMS
        for (unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
            if (vals[i] >= 128) {
                sum += vals[i];
            }
        }
    }
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return sum;
}

/** Can't compile on ARM (╯°□°）╯︵ ┻━┻ */
/***** Useless code of x86 sum_simd *****/

// long long int sum_simd(int vals[NUM_ELEMS]) {
//     clock_t start = clock();
//     // This is a vector with 127s in it... Why might you need this?
//     __m128i _127 = _mm_set1_epi32(127);
//     // This is where you should put your final result!
//     long long int result = 0;
//     /* DO NOT DO NOT DO NOT DO NOT WRITE ANYTHING ABOVE THIS LINE. */

//     for (unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
//         /* YOUR CODE GOES HERE */
//         int sum[4];
//         __m128i sum_v = _mm_set1_epi32(0);
//         for (unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
//             // compare if vals > 127
//             __m128i mask =
//                 _mm_cmpgt_epi32(_mm_loadu_si128((__m128i*)(vals + i)), _127);

//             // reduce vals smaller than 128 to 0
//             __m128i cur_vector =
//                 _mm_and_si128(_mm_loadu_si128((__m128i*)(vals + i)), mask);
//             // add to accumulator
//             sum_v = _mm_add_epi32(sum_v, cur_vector);
//         }
//         // save to SUM
//         _mm_storeu_si128((__m128i*)sum, sum_v);
//         /* You'll need a tail case. */
//         for (unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
//             if (vals[i] >= 128) {
//                 sum[0] += vals[i];
//             }
//         }
//         result += sum[0] + sum[1] + sum[2] + sum[3];
//     }

//     clock_t end = clock();
//     printf("Time taken: %Lf s\n", (long double)(end - start) /
//     CLOCKS_PER_SEC); return result;
// }

/** Redo it with ARM NEON
 * Result: 2x the speed of naive sum */
long long int sum_simd_arm(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    long long int result = 0;

    // This is a vector with 127s in it... Why might you need this?
    int32x4_t _127 = vdupq_n_s32(127);
    // int32_t sums_arr[NUM_ELEMS / 4 + 1];

    for (unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        /* YOUR CODE GOES HERE */
        int32_t sum[4] = {0};
        int32x4_t sum_v = vdupq_n_s32(0);
        for (unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
            // compare if vals > 127
            int32x4_t mask = vcgtq_s32(vld1q_s32(vals + i), _127);
            // reduce vals smaller than 128 to 0
            int32x4_t cur_vector = vandq_s32(vld1q_s32(vals + i), mask);
            // add to accumulator
            sum_v = vaddq_s32(sum_v, cur_vector);
        }
        // save to SUM
        vst1q_s32(sum, sum_v);
        /* You'll need a tail case. */
        for (unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
            if (vals[i] >= 128) {
                sum[0] += vals[i];
            }
        }

        result += sum[0] + sum[1] + sum[2] + sum[3];
    }

    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return result;
}

/***** Useless code of x86 sum_simd_unrolled *****/

// long long int sum_simd_unrolled(int vals[NUM_ELEMS]) {
//     clock_t start = clock();
//     __m128i _127 = _mm_set1_epi32(127);
//     long long int result = 0;
//     for (unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
//         /* COPY AND PASTE YOUR sum_simd() HERE */
//         /* MODIFY IT BY UNROLLING IT */

//         /* You'll need 1 or maybe 2 tail cases here. */
//     }
//     clock_t end = clock();
//     printf("Time taken: %Lf s\n", (long double)(end - start) /
//     CLOCKS_PER_SEC); return result;
// }

/** REDO unrolling...
 * Result: 1.804936 s (1.1x speedup)*/
long long int sum_simd_unrolled_arm(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    long long int result = 0;

    int32x4_t _127 = vdupq_n_s32(127);

    for (unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        int32_t sum[4] = {0};
        int32x4_t sum_v = vdupq_n_s32(0);

        // unroll into 16
        for (unsigned int i = 0; i < NUM_ELEMS / 16 * 16; i += 16) {
            int32x4_t mask_1 = vcgtq_s32(vld1q_s32(vals + i), _127);
            int32x4_t mask_2 = vcgtq_s32(vld1q_s32(vals + i + 4), _127);
            int32x4_t mask_3 = vcgtq_s32(vld1q_s32(vals + i + 8), _127);
            int32x4_t mask_4 = vcgtq_s32(vld1q_s32(vals + i + 12), _127);

            int32x4_t cur_vector_1 = vandq_s32(vld1q_s32(vals + i), mask_1);
            int32x4_t cur_vector_2 = vandq_s32(vld1q_s32(vals + i + 4), mask_2);
            int32x4_t cur_vector_3 = vandq_s32(vld1q_s32(vals + i + 8), mask_3);
            int32x4_t cur_vector_4 =
                vandq_s32(vld1q_s32(vals + i + 12), mask_4);

            sum_v = vaddq_s32(sum_v, cur_vector_1);
            sum_v = vaddq_s32(sum_v, cur_vector_2);
            sum_v = vaddq_s32(sum_v, cur_vector_3);
            sum_v = vaddq_s32(sum_v, cur_vector_4);
        }

        vst1q_s32(sum, sum_v);

        for (unsigned int i = NUM_ELEMS / 16 * 16; i < NUM_ELEMS; i++) {
            if (vals[i] >= 128) {
                sum[0] += vals[i];
            }
        }

        result += sum[0] + sum[1] + sum[2] + sum[3];
    }

    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return result;
}
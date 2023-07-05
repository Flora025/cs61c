#include "bit_ops.h"
#include <stdio.h>

// You may ONLY use bitwise operations such as and (&), or (|), xor (^),
// not (~), left shifts («), and right shifts (»)

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x, unsigned n) {
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns
    // 0 or 1)
    return (x >> n) & 1;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned* x, unsigned n, unsigned v) {
    // YOUR CODE HERE
    // bit op:
    unsigned mask = (1 << n);
    // clear nth bit
    *x &= ~mask;
    // complement or retain
    *x |= (v << n);
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned* x, unsigned n) {
    // YOUR CODE HERE
    *x ^= (1 << n);
}

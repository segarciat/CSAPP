# Exercise 2.66

Write code to implement the following function

```c
/* 
 * Generate mask indicating leftmost 1 in x. Assume w=32
 * For example, 0xFF00 -> 0x8000, and 0x6600 -> 0x4000.
 * If x = 0, then return 0 */
int leftmost_one(unsigned x);
```

Your function should follow the bit-level integer coding rules (page 128),
except that you may assume that *w* = 32 bits.

Your code should contain a total of at most 15 arithmetic, bitwise, and
logical operations.

*Hint*: First transform `x` into a bit vector of the form [0...011...1].

## Solution

I began by thinking about how the hint helps in solving the problem. If
`transformedx` is the vector in the recommended form, where the leftmost
bit of `transformedx` is equivalent to that of `x`, then shifting it by
right and subtracting it from `transformedx - (transformedx >> 1)` gives
the mask, since its only 1 bit will be the least significant bit of `x`.

To convert `x` to `xtransformedx`, we need to set bits to 1, so we'll need
the `|` operator. In the worst case, `x` will have 1 in the most significant
bit, and 0 otherwise. In this case, we need to copy the most significant
1 to the 31 positions right of it. We can do it by ORing `x` and a shifted
version of itself repeatedly.

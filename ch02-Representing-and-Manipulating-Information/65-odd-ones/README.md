# Exercise 02-65

Write code to implement the following function

```c
/* Return 1 when x contains an odd number of 1s; 0 otherwise 
 * Assume w=32
 */
int odd_ones(unsigned x);
```

Your functino should follow the bit-level integer coding rules (page 128),
except that you may assume that data type `int` has *w* = 32 bits.

Your code shoudl contain a total of at most 12 arithmetic, bitwise, and
logical operations.

## Solution

The solution is to XOR all of the bits of `x`. The result is 1 if there is
an odd number of 1s. To do this, we can use the C XOR operator `^` to XOR
`x` with a shifted version of itself, eventually placing the result in the
least significant bit. From there, a logical OR operation `||` with 0 as
the right side operand yields the result. 

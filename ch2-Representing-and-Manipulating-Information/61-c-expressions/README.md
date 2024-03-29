# Exercise 02-61

Write C expressions that evaluate to 1 when the fllowing conditions are true and to 0
when they are false. Assume `x` is of type `int`.

A. Any bit of `x` equals 1.
B. Any bit of `x` equals 0.
C. Any bit in the least significant byte of `x` equals 1.
D. Any bit in the most significant byte of `x` equals 0.

## Solution

A. `x || 0`: or `x != 0`, since 0 has only 0s in its binary representation.

B. `~x || 0`: If `x` has a 0 bit, then `~x` has 1 bit, so `~x || 0` yields 1. Or simpler,`x != -1`,
since `-1` has all 1s in its binary representation.

C. `(x & 0xFF) || 0`
D. `((x >> (8*(sizeof(int)-1))) & 0xFF) != 0xFF`, or since `int` is signed, the fact that `>>` is arithmetic
in this case means that when `x` has only 1 bits in its most significant byte, that shifting to the least
significant byte results in `x` becoming `-1`. Hence, another test is `(x >> (8(sizeof(int)-1))) != -1`.

```c
/* Shift by w-8 */
int shiftAmount = (sizeof(int) - 1) << 3;

/* Get most significant byte */
int xmsbyte = (x >> shiftAmount) & 0xFF;
return ~xmsbyte || 0;
```

# Exercise 02-61

Write C expressions that evaluate to 1 when the fllowing conditions are true and to 0
when they are false. Assume `x` is of type `int`.

A. Any bit of `x` equals 1.
B. Any bit of `x` equals 0.
C. Any bit in the least significant byte of `x` equals 1.
D. Any bit in the most significant byte of `x` equals 0.

## Solution

A. `x || 0`
B. `~x || 0`
C.

```c
/* Shift by w-8 */
int shiftAmount = (sizeof(int) - 1) << 3;

/* Get most significant byte */
int xmsbyte = (x >> shiftAmount) & 0xFF;
return xmsbyte || 0;
```

D.

```c
/* Shift by w-8 */
int shiftAmount = (sizeof(int) - 1) << 3;

/* Get most significant byte */
int xmsbyte = (x >> shiftAmount) & 0xFF;
return ~xmsbyte || 0;
```

# Exercise 02-64

Write code to implement the following function:

```c
/* Return 1 when any odd bit of x equals 1; 0 otherwise.
 * Assume w=32
 */
int any_off_one(unsigned x);
```

Your function should follow the bit-level coding rules (page 128),
except that you may assume that data type `int` has *w* = 32 bytes.

## Solution

Note that the 4-bit binary number `0101` has only odd ones. This number
is equivalent to `0x5`. Since we assume *w* is 32, and since each hex
is equivalent to 4 bits, we can repeat this hex digit 8 times and use it
to determine odd ones.

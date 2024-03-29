# Exercise 2.59

Write a procedure `is_little_endian` that will return 1 when compiled and run
on a little-endian machine, and will return 0 when compiled and run on a big
endian machine. This program should run on any machine, regardless of its
word size.

## Solution

My solution looks at the bit-level representation of `1`, and sees if the first
byte has value `0x1`.

Run and compile as follows:

```bash
gcc -o is_little_endian main.c endianness.c
./is_little_endian
```

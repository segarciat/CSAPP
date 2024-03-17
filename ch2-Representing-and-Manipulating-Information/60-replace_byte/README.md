# Exercise 02-60

Suppose we number the bytes in a *w*-bit from 0 (least significant) to *w/8 - 1* (most significant).
Write code for the following C function, which will return an unsigned value in which byte *i*
of argument `x` has been replaced by byte `b`:

```c
unsigned replace_byte(unsigned x, int i, unsigned char b);
```

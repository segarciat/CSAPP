#Exercise 02-59

Write a C expression that will yield a word consisting of the least significant byte of
`x` and the remaining bytes of `y`. For operands `x = 0x89ABCDEF` and `y=0x76543210`,
this would give `0x765432EF`.

## Solution

```c
(x & 0xFF) | (y & ~0xFF)
```

This works because `0xFF` has all 1s in the least significant byte, and 0 otherwise,
and the logical NOT `~` causes `~0xFF` to have all 0s in the least significant byte
and 1 otherwise.

# Exercise 02-55

Compile and run the sample code that uses `show_bytes` (file `show-bytes.c`)
on different machines to which you have access. Determine the byte orderings
of these machines.

## Solution

On my Windows 11 machine, after running it in the corresponding 64-bit WSL environment,
I got the following output:

```
 39 30 00 00
 00 e4 40 46
 a8 d1 5e 54 ff 7f 00 00
```

The number `12345` has hexadecimal representation `0x00003039`. This suggests my machine
uses little-endian.

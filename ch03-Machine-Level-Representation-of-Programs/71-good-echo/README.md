# Exercise 3.71

Write a function `good_echo` that reads a line from standard
input and writes it to standard output. Your implementation should work
for an input line of arbitrary length. You may use the library function
`fgets`, but you must make sure function works correctly even when
the input line requires more space than you have allocated for your buffer.
Your code should also check for error conditions and return when one is
encountered. Refer to the definitions of the standard I/O functions for
documentation.

## Solution

The library function `fgets` does most of the work. It accepts a buffer,
a maximum size of characters that the buffer can hold, and a stream to
read from. The stream is simply `stdin`, defined in `<stdio.h>`. I also
decided to use `BUFSIZ` from the same header. Error and EOF can be
detected by a return value of `NULL`, at which point we end the function.
To detect a newline character, it's convenient to make use of the fact
that `printf` returns the number of characters printed, excluding the
null byte. If it's negative, an error occurred; otherwise, subtracting
1 from it yields the position of the last character printed. If that
character is a newline character, then we're done.

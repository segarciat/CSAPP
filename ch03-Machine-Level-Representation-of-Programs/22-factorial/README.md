# Exercise 03-22

A. What is the maximum value of *n* for which we can represent *n!*
with a 32-bit `int`?

B. What about for a 64-bit `long`?

## Result

I was stumped on this, but the book provides the solution to this practice
problem. It uses the `tmult_ok` from Practice Problem 2.35 to check for
multiplication overflow. Doing so, one can print a factorial table that
stops at the last value of `n` before overflow.

A. `n=12` is the maximum before overflow.
B. `n=20` is the maximum before overflow.

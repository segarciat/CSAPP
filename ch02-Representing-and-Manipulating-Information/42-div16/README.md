# Practice Problem 2.42

Write a function `div16` that returns the value `x/16` for integer argument `x`.
Your function should not use division, modulus, multiplication, any conditionals
(`if`, or `?:`), any comparison operators (e.g., `<`, `>`, or `==`), or any loops.
You may assume that data type `int` is 32 bits long and uses a two's-complement
representation and that right shifts are performed arithmetically.

## Running Tests

The one-liner is unit-tested with glib. Assuming a Linux environment, install the following:

```bash
# Includes a C compiler, among other things.
sudo apt-get install gcc

# Helps in getting the right includes and library paths for linking with external libraries, i.e., glib.
sudo apt-get install pkg-config

# Simplifies compilation.
sudo apt-get install make

# General-purpose library, including test framework.
sudo apt install libglib2.0-dev
```

Compile with `make`, then run the executable with the tests:

```bash
make
./test-div16
```


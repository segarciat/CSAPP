# Practice Problem 2.27

Write a function with the following prototype:

```c
/* Determine whether arguments can be added without overflow */
int uadd_ok(unsigned x, unsigned y);
```

This function should return 1 if arguments `x` and `y` can be added without causing overflow.

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
./test-overflow
```


# Practice Problem 2.36

For the case where data type `int` has 32 bits, devise a version of `tmult_ok` (see Problem 2.35)
that uses the 64-bit precision of data type `int64_t`, without using division

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


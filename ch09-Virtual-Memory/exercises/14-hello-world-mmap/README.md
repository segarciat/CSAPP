# Exercise 9.14

Given an input file `hello.txt` that consists of the string `Hello, world!\n`, write a
C program that uses `mmap` to change the contents of `hello.txt` to `Jello, world!\n`.

## Solution

```bash
# Create hello.txt, use -e to enable backslash sequence interpretation 
echo -e "Hello, world! \n" > hello.txt

# Compile
gcc mmap_hello.c

# Run
./a.out hello.txt

# Verify
cat hello.txt
```

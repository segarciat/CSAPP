# Exercise CSAPP

This repository consists of my self-study journey through the book *Computer Systems: A Progammer's Perspective*
by Bryant and O'Hallaron (3rd edition). See the [book website](https://csapp.cs.cmu.edu/).

## Labs

The companion website of the book has [lab assignments](https://csapp.cs.cmu.edu/3e/labs.html). The labs
are in the `./labs` directory, and each contains the associated supporting files, modified according
to the lab instructions. For example, the *Data Lab* is in `./labs/datalab-handout`, and the only modified
file was `bits.c` as instructed. We can build the lab and supporting files and verify the implementations as follows:

```bash
# Build lab files
cd labs/datalab-handout
make

# Verify adherence to rules
./dlc bits.c

# Run unit tests
./btest
```

### Dependency Packages

When I tried running `make` in the data lab directory, It failed with the following error:

```
...
/usr/include/limits.h:26:10: fatal error: bits/libc-header-start.h: No such file or directory
   26 | #include <bits/libc-header-start.h>
   ...
```

According to Nick on [this Stack Overflow](https://stackoverflow.com/questions/54082459/fatal-error-bits-libc-header-start-h-no-such-file-or-directory-while-compili), this has to do with the fact that the `make` command is trying to compile a 32-bit binary by running `gcc` with `-m32`:

```bash
gcc -O -Wall -m32 -lm -o btest bits.c btest.c decl.c tests.c
```

But on a 64-bit platform, it normally only comes with the 64-bit libraries. The fix was to install:

```bash
sudo apt-get install gcc-multilib
```

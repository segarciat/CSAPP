# Exercise 02-63

Fill in code for the following C functions. Function `srl` performs a logical right shift using
an arithmetic right shift (given by value `xsra`), followed by other operations not including
right shifts or division. Functions `sra` performs an arithmetic right shift using a logical
right shift (given by value `xsrl`), followed by other operations not including right shifts or
division. You may use the compitation `8*sizeof(int)` to determine the *w*, the number of bits
in data type `int`. The shift amount `k` can range from 0 to *w-1*.

```c
unsigned srl(unsigned x, int k) {
	/* Perform shift artihmetically */
	unsigned xsra = (int) x >> k;
	/* Fill in rest */
}

int sra(int x, int k) {
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;
}
```

/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	/* Computes x ^ y as (~x & y) | (x & ~y) using DeMorgan's Laws */
	int w1 = (~x &  y);
	int w2 = ( x & ~y);
  return ~(~w1 & ~w2);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	/* Assumes int is 32 bit to place 1 in most significant bit */
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
	/* Tmax + 1 == Tmin, so x is Tmax iff x + 1 = TMin. (x + 1) == Tmin iff -(x+1) == x+1 and x != -1 */
	int isNegativeOne = !(x ^ ~0);
	int xplus1 = x + 1;
	int isOwnNegative = !((~xplus1 + 1) ^ xplus1);
	return (!isNegativeOne) & isOwnNegative;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	/* Note that hex 0xA = 1010 in binary */
	/* AND all odd bits and place result at position 1 */
  x &= x >> 16;
  x &= x >> 8;
  x &= x >> 4;
  x &= x >> 2;
  return (x & 2) >> 1;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* Definition of negation */
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /* Checks MSByte is 0x3 and LSByte is less than 10 */
  int validMSByte = !((x >> 4) ^ 0x3);
  int lsByte = x & 0xF;
  int lsByteLessThan10 = !(lsByte ^ 0x8) | !(lsByte ^ 0x9) | !(lsByte & 0x8);
  return validMSByte & lsByteLessThan10;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	/* 
	 * Transform x to 0 if x is 0, and -1 otherwise
	 */
	 int t = ~(!(!x)) + 1;
  return (t & y) | (~t & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	/* x <= y iff x == y or x < y, and x < y if (x - y overflows) XOR (x-y is negative) */
	int xEqualsY = !(x ^ y);
	int xMinusY = x + (~y + 1);

	int signMask = (1 << 31);

	int signXminusY = xMinusY & signMask;
	int signX = x & signMask;
	int signY = x & signMask;

	int overflows = (signX ^ signY) & (signX ^ signXminusY);

  return xEqualsY | !!(signXminusY ^ overflows);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	// x == 0 iff ~x == -1, and ~x is -1 iff the AND of all the bits is 1.
	int notX = ~x;
	notX &= notX >> 16;
	notX &= notX >>  8;
	notX &= notX >>  4;
	notX &= notX >>  2;
	notX &= notX >>  1;
  return notX & 0x1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>

*  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
	/* Shift total of 32 places and increase count as long as we are not at -1 (for negatives) or 0 (for positives) */

	int minusOne = ~0;
	int minus4 = ~4 + 1;
	int normalize = !(x^0) + (~!(x^minusOne) + 1);	/* -1 if x is -1 ; 1 if x is 0 ; 0 otherwise */
	int y = x = (x + normalize);					/* y is not -1 and also not 0 */

	int signMask = (1 << 31);
	int countMask = !(signMask & x) + minusOne;		/* -1 if x < 0; 0 otherwise */
	int count = 0;

	/* If x is negative, increase if y is not -1 ; otherwise, increase if y is not 0 */
	count = count + !!(y^countMask);
	y = y >> 4;
	count = count + !!(y^countMask);
	y = y >> 4;
	count = count + !!(y^countMask);
	y = y >> 4;
	count = count + !!(y^countMask);
	y = y >> 4;
	count = count + !!(y^countMask);
	y = y >> 4;
	count = count + !!(y^countMask);
	y = y >> 4;
	count = count + !!(y^countMask);
	y = y >> 4;
	count = count + !!(y^countMask);
	y = y >> 4;

	/* Multiply by 4 (since we shifted by 4 each time) */
	count = count << 2;

	/* Backtrack */
	y = (x >> (count + minus4));
	count = count + minus4;

	/* Same as before, but test 1 bit at a time */
	count = count + !!(y^countMask);
	y = y >> 1;
	count = count + !!(y^countMask);
	y = y >> 1;
	count = count + !!(y^countMask);
	y = y >> 1;
	count = count + !!(y^countMask);
	y = y >> 1;

	/* Anything that is not 0 and -1 requires at least 2 bits */
	return count + !(normalize);
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
	/* 
	 * If 0, return 0
	 * If NaN return NaN: This means exp is all 1s and fraction is nonzero.
	 * If infinity return infinity: This means exp is all 1s and fraction is zero.
	 * Otherwise, increase exp  bits by 1. If becomes all 1s, make fraction bits 0.
	 */
#define SIGN_POSITION 31
#define EXPONENT_POSITION 23
	int minusOne = ~0;
	int signMask = 1 << SIGN_POSITION;
	int expMask = minusOne << EXPONENT_POSITION;
	int fractionMask = ~expMask;
	int sign, exponent, fraction, shiftedExpPlus1;
	expMask = expMask ^ signMask;				/* Eliminate sign bit */
	exponent = uf & expMask;
	fraction = uf & fractionMask;
	if (!(exponent ^ expMask))					/* Represents NaN or Infinity */
		return uf;
	
	sign = uf & signMask;
	if (!exponent)								/* Denormalized; multiply fraction by 2 */
		return sign | (fraction << 1);
	shiftedExpPlus1 = ((exponent >> EXPONENT_POSITION) + 1) << EXPONENT_POSITION;
	if (!(expMask ^ shiftedExpPlus1))			/* Product is pos or neg infinity */
		return sign | expMask;
	return sign | shiftedExpPlus1 | fraction;	/* Normalized */
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
	/*
	 * It's 1 when fraction bits are all 0 and all exponent bits except the leading bit are 1.
	 * Largest representable has 23 fraction bits: 1.***1e^{23} => (Remove leading 1) => 1***1
	 * Exponent is 23, add bias of 127 to get 150, or just 1 in leading bit and 0x17 in hex.
	 * Anything beyond that is too large and should be INT_MIN
	 * 
	 */
#define SIGN_POSITION 31
#define EXPO_POSITION 23
#define BIAS 127
	/* Compute floating field bit masks */
	unsigned minusOne = ~0;
	unsigned signMask = 1 << SIGN_POSITION;
	unsigned expMask = minusOne << EXPO_POSITION;
	unsigned fractionMask = ~expMask;

	int encodedExponent, realExponent;
	int shiftAmount;
	int sign, signExtended;
	int implicitLeading1Bit, significand;

	expMask ^= signMask; /* Eliminate sign */

	/* Extract encoded exponent and compute real exponent */
	encodedExponent = uf & expMask;
	realExponent = (encodedExponent >> EXPO_POSITION) + (~BIAS + 1);
	if (realExponent & signMask)	/* Negative exponent indicates number less than 1 */
		return 0;
	shiftAmount = EXPONENT_POSITION + (~realExponent + 1);
	if (shiftAmount & signMask)				/* Exceeds maximum int representable by float */
		return signMask;					/* Equivalent to INT_MIN */

	/* Extract and extend sign into exponent position */
	sign = uf & signMask;
	signExtended = sign >> 8;

	/* Build significand */
	implicitLeading1Bit = (1 << EXPO_POSITION);
	significand = implicitLeading1Bit | (uf & fractionMask);

	/* Shift and drop any fractional bits */
	return (signExtended | significand) >> shiftAmount;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
	/*
	 * Bias = 127
	 * Since e is 8 bits, it can range from 0 to 255, inclusive.
	 * If normalized (e != 0 && e != 255), then E = e - bias, ranging from 1-127 to 254 - 127 (-126 to 127)
	 * If denormalized (e == 0), thne E = 1 - bias = -126
	 * 
	 * Smallest float is the smallest denormalized, with a 1 in least significand fraction bit.
	 * This means we have 2^(-126) * 2^(-23) = 2^(-149). Any smalled exponent means we return 0 (underflow).
	 * Reject if x is smaller than -149 as 0
	 *
	 * Largest float is when exponent is largest, so 2^(127)
	 * Anything larger overflows and is thus +INF
	 */
#define BIAS 127
#define DENORM_EXP (1 - BIAS)
#define MAX_NORM_EXP 127
#define MIN_NORM_EXP (-126)
#define EXPONENT_POSITION 23
	unsigned exponentMask = 0xFF;
	int biasedExponent;
	int fractionBitPosition;
	if (x < DENORM_EXP)					/* Underflow */
		return 0;
	if (x > MAX_NORM_EXP) {				/* Too large */
		return exponentMask << EXPONENT_POSITION;
	}
	if (x >= MIN_NORM_EXP) {			/* Normalized */
		 biasedExponent = (x + BIAS) & exponentMask;
		return biasedExponent << EXPONENT_POSITION;
	}
	fractionBitPosition = MIN_NORM_EXP - x;
	return (1 << (EXPONENT_POSITION - fractionBitPosition));
}

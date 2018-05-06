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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {

  return x >> (n << 3) & 0xff;

}
// 先把x移n<<3(即8n)个位  再用x&0xFF生成一个由x的最低有效字节组成的字 

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  return x >> n & ~(((1 << 31) >> n) << 1);
}
// 先x>>n（算术右移） 在利用1移位把前面移位的结果都变成0

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int tmp = 0x01;
  tmp = tmp | (tmp << 8);
  tmp = tmp | (tmp << 16);
  int result = tmp & x;
  result += tmp & (x >> 1);
  result += tmp & (x >> 2);
  result += tmp & (x >> 3);
  result += tmp & (x >> 4);
  result += tmp & (x >> 5);
  result += tmp & (x >> 6);
  result += tmp & (x >> 7);

  result += (result >> 16);
  result += (result >> 8);

  return result&0xff;
}

// 先分成4个部分（每部分8位）进行计算 然后再把4部分的结果通过对半得出最后的结果
// 按照8位的原因大概是结果最大32， 2 4位都不够  一定要&0xff 取最低有效字节


/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  return (((~x + 1) | x) >> 31) + 1;
}
// 关键是判断0 除了0其他数字与其相反数首位（符号位）一定不同 所以按位或的话只有零的首位还是零
// 如果是0 则>>31的结果为0  如果不是0则结果为-1（所有的位都是1）再加1
// 位运算求相反数： ~x+1
// 注意运算符优先级……不确定的最好都加上括号


/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
// 最小的二进制补码 也就是0x80000000

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int shift = ~n + 33; // 即32-n
  return !(x ^ ((x << shift) >> shift));
  //若前32-n位的都相同则可以

  // int sign = x >> 31; //得到其符号位（0或-1）
  // return !((-x & sign) + (x & ~sign) >> (n + ~0))

}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int sign = x >> 31;
    int result = x + (sign & ((1 << n) + (~0)));
    return result >> n;
}
// 若x>=0 就是x >> n
// 若x<0  不管符号位的话就是 (x+（1 << n) -1) >> n


/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
}
// 取相反数： 按位取反然后+1

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  int sign = x >> 31; 
  int zero = !x; // 是否是0
  return !(sign | zero); 
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int signx = x >> 31;
  int signy = y >> 31;

  int sign = !(signx ^ signy); //相同的话 1
  int tmp = (x + ~y) >> 31; // x-y 的符号 
  return (sign & tmp) | (!sign & signx);
}
// 分类 如果同号：右边式子结果为0 最终由x-y的符号决定
// 如果异号： 若x<0则返回1 （左0右1结果1） 若x>0 则由x-y符号决定(右0)

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    int log;
    
    log = (!!(x >> 16)) << 4; // 判断是不是1 如果是就乘上2^4 下同
    log = log + ((!!(x >> (log + 8))) << 3); 
    log = log + ((!!(x >> (log + 4))) << 2);
    log = log + ((!!(x >> (log + 2))) << 1); 
    log = log + (!!(x >> (log + 1)));
  
  return log;
}

// 通过两次取非来转换成布尔值（取值只有0和1）
// 每次分成两半，搜索最高位为1的位置 


//
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  unsigned tmp = 0x80000000;
  unsigned NaN = 0x7FC00000;
  unsigned inf = 0xFFC00000;
  if(uf == NaN || uf == inf){
    return uf;
  }
 return uf ^ tmp;
}
// 取反 注意特殊之

/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  unsigned sign = 0, shiftLeft = 0, flag = 0, tmp;  
  unsigned result = x;  

  if(!x){
    return 0;  
  } else if(x < 0){  
    sign = 0x80000000;  
    result = -x;  
  }

  while(1){
    tmp = result;  
    result <<= 1;  
    shiftLeft++;  
    if( tmp & 0x80000000 ){
      break; 
    }
  }  


  if((result & 0x01FF) > 0x0100){
      flag = 1;
  }else if((result & 0x03FF) == 0x0300){
      flag = 1;
  }else{
      flag = 0;
  }
    
    
  return sign + (result >> 9) + ((159 - shiftLeft) << 23) + flag;  
}


/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  unsigned expo = uf & 0x7F800000;
  unsigned sign = uf & 0x80000000;
  unsigned frac = uf & 0x007FFFFF;
  
  if(expo == 0){
    uf = (frac << 1) | sign;
  } else if (expo != 0x7F800000) {
    uf = uf + 0x00800000;
  }

  return uf;
}

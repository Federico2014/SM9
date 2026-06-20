#ifndef BIGINT_H
#define BIGINT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Maximum 1024-bit length in 32-bit words
#ifndef BI_MAXLEN
#define BI_MAXLEN 32
#define DEC 10
#define HEX 16
#endif

//typedef long long __int64;
typedef struct CBigInt_Tag{
// Length in base 0x100000000
unsigned m_nLength;
// Values of each digit in base 0x100000000
unsigned long m_ulValue[BI_MAXLEN];
}CBigInt;



/*****************************************************************
Big Integer Arithmetic Function Declarations
Init: Initialize a big integer to zero
Mov: Move/assign operations
Cmp: Comparison operations (==, !=, >=, <=)
Add: Addition operations (+)
Sub: Subtraction operations (-)
Mul: Multiplication operations (*)
Div: Division operations (/)
Mod: Modulo operations (%)
*****************************************************************/
void CBigIntInit(CBigInt *A);
void Mov_Big_Long(CBigInt * N, unsigned long A);
void Mov_Big_Big(CBigInt *N, CBigInt A);
void Add_Big_Big(CBigInt *Y, CBigInt N, CBigInt A);
void Add_Big_Long(CBigInt *Y, CBigInt N, unsigned long A);
void Sub_Big_Big(CBigInt *Y,CBigInt N, CBigInt A);
void Sub_Big_Long(CBigInt *Y, CBigInt N, unsigned long A);
void Mul_Big_Big(CBigInt *Y, CBigInt N, CBigInt A);
void Mul_Big_Long(CBigInt *Y, CBigInt N, unsigned long A);
void Div_Big_Big(CBigInt *M,CBigInt N, CBigInt A);
void Div_Big_Long(CBigInt *Y, CBigInt N, unsigned long A);
void Mod_Big_Big(CBigInt *Z,CBigInt N, CBigInt A);
unsigned long Mod_Big_Long(CBigInt N, unsigned long A);
int Cmp(CBigInt N,CBigInt A);

/*****************************************************************
String Conversion Functions
Get: Parse string in base 10 or 16 to big integer
Put: Convert big integer to string in base 10 or 16
*****************************************************************/
void Get(CBigInt *N, char* str, unsigned int system);
char* Put(CBigInt N, unsigned int system);
unsigned char* PutFieldElement(CBigInt N, unsigned int system); // Pad with leading zeros for field elements
/*****************************************************************
Extended Euclidean Algorithm and Modular Exponentiation
Inv: Extended Euclidean algorithm for modular inverse
Exp: Square-and-multiply algorithm for modular exponentiation
*****************************************************************/
void Inv(CBigInt *Z, CBigInt N, CBigInt A);
void Exp(CBigInt *Z, CBigInt N, CBigInt A, CBigInt B);
#endif

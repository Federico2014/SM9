#ifndef BNFIELD12_H
#define BNFIELD12_H

#include "sm9/core/field4.h"


typedef struct
{
    BNField4 re;
	BNField4 im;
	BNField4 sq;
}BNField12;


void BNField12_init(BNField12 *p); // Initialize BNField12

void F12_construct(BNField12 *p, BNField4 re, BNField4 im, BNField4 sq); // BNField12 constructor

void F12_normorlize(BNField12 *p, BNField12 b);  // Normalization

void  F12_assign(BNField12 *p, BNField12 b);  // Assignment: p = b

void  F12_assign_1(BNField12 *p); // Assignment: p = 1

void  F12_add(BNField12 *p, BNField12 b1, BNField12 b2); // Addition of two BNField12 elements

void  F12_add_F4(BNField12 *p, BNField12 b, BNField4 k); // Add BNField4 to BNField12

void  F12_substract(BNField12 *p, BNField12 b1, BNField12 b2); // Subtraction of two BNField12 elements

void  F12_substract_F4(BNField12 *p, BNField12 b, BNField4 k); // Subtract BNField4 from BNField12

int F12_isZero(BNField12 b); // Return 1 if element is zero, otherwise return 0

int F12_isOne(BNField12 b); // Return 1 if element is one, otherwise return 0

int F12_equal(BNField12 b1, BNField12 b2); // Compare two elements, return 1 if equal, otherwise return 0

void  F12_negate(BNField12 *p, BNField12 b); // Negation of BNField12 element

void  F12_frobenius(BNField12 *p, BNField12 b); // Frobenius map on BNField12

void  F12_GFrobenius(BNField12 *p, BNField12 b, unsigned int e); // Generalized Frobenius map on BNField12

/*
   (a+bw+cw^2)(a'+b'w+c'w^2):
       = aa' + ((b+c)(b'+c')-bb'-cc')v + ((a+b)(a'+b')-aa'-bb'+cc'v)w
	           + ((a+c)(a'+c')-aa'-cc'+bb')w^2
 */
void  F12_multiply(BNField12 *p, BNField12 b1, BNField12 b2);

void  F12_multiply_F4(BNField12 *p, BNField12 b, BNField4 k); // Multiply by BNField4: (a+bw+cw^2)k = ka+kbw+kcw^2

void  F12_multiply_i(BNField12 *p, BNField12 b, int k); // Multiply by small integer: (a+bw+cw^2)k = ka+kbw+kcw^2

void  F12_multiply_I(BNField12 *p, BNField12 b, CBigInt k); // Multiply by CBigInt: (a+bw+cw^2)k = ka+kbw+kcw^2

/*
   Square of BNField12 element:
   (a+bw+cw^2)^2:
       = a^2 + ((b+c)^2-b^2-c^2)v + ((a+b)^2-a^2-b^2+c^2 v)w
	           + ((a+c)^2-a^2-c^2+b^2)w^2
 */
void  F12_square(BNField12 *p, BNField12 b);

/*
   Inverse of BNField12 element:
   (a+bw+cw^2)^(-1) = (A+Bw+Cw^2)/(bCv+aA+cBv)
   where A = a^2-bcv
         B = c^2 v-ab
         C = b^2-ac
 */
void  F12_inverse(BNField12 *p, BNField12 b);

void F12_exp(BNField12 *p, BNField12 b, CBigInt e); // Exponentiation: *p = b^e, e must be >= 0

void F12_toString_d(BNField12 b, unsigned int system); // Print BNField12 in standard format

void F12_toString(BNField12 b, unsigned int system); // Print BNField12 in SM9 standard format

#endif

#ifndef BNFIELD4_H
#define BNFIELD4_H

#include "sm9/core/field2.h"


typedef struct
{
    BNField2 re;
	BNField2 im;
} BNField4;


void BNField4_init(BNField4 *p); // Initialize BNField4

void F4_construct(BNField4 *p, BNField2 re, BNField2 im); // BNField4 constructor: (re, im)

void F4_normorlize(BNField4 *p, BNField4 b); // Normalization

void F4_construct_F2(BNField4 *p, BNField2 re); // BNField4 constructor with imaginary part = 0

void F4_assign(BNField4 *p, BNField4 b);  // Assignment: p = b

void  F4_add(BNField4 *p, BNField4 b1, BNField4 b2); // Addition of two BNField4 elements

void  F4_add_F2(BNField4 *p, BNField4 b, BNField2 k); // Add BNField2 to BNField4

void  F4_substract(BNField4 *p, BNField4 b1, BNField4 b2); // Subtraction of two BNField4 elements

void  F4_substract_F2(BNField4 *p, BNField4 b, BNField2 k); // Subtract BNField2 from BNField4

int F4_isZero(BNField4 b); // Return 1 if element is zero, otherwise return 0

int F4_isOne(BNField4 b); // Return 1 if element is one, otherwise return 0

int F4_equal(BNField4 b1, BNField4 b2); // Compare two elements, return 1 if equal, otherwise return 0

void  F4_negate(BNField4 *p, BNField4 b); // Negation of BNField4 element

void F4_frobenius(BNField4 *p, BNField4 b); // Frobenius map on BNField4

void  F4_GFrobenius(BNField4 *p, BNField4 b, unsigned int e); // Generalized Frobenius map on BNField4

void  F4_multiply(BNField4 *p, BNField4 b1, BNField4 b2); // (a+bv)(a'+b'v) = (aa'+bb'u)+((a+b)(a'+b')-aa'-bb')v

void  F4_multiply_F2(BNField4 *p, BNField4 b, BNField2 k); // Multiply by BNField2: (a+bu)k = ka+kbu

void  F4_multiply_i(BNField4 *p, BNField4 b, int k); // Multiply by small integer: (a+bu)k = ka+kbu

void  F4_multiply_I(BNField4 *p, BNField4 b, CBigInt k); // Multiply by CBigInt: (a+bu)k = ka+kbu

void  F4_multiply_v(BNField4 *p, BNField4 b); // Multiply by v: (a+bv)v = bu+av

void  F4_square(BNField4 *p, BNField4 b); // Square: (a+bv)^2 = a^2+b^2u+2abv

void  F4_inverse(BNField4 *p, BNField4 b); // Inverse: (a+bv)^(-1) = (a-bv)/(a^2-b^2u)

void F4_toString(BNField4 b, unsigned int system); // Print BNField4 in specified base

#endif

#ifndef BNFIELD2_H
#define BNFIELD2_H

#include "sm9/sm9/params.h"


typedef struct
{
    CBigInt re;
	CBigInt im;

}BNField2;


void BNField2_init(BNField2 *p); // Initialize BNField2

void F2_construct(BNField2 *p, CBigInt re, CBigInt im); // BNField2 constructor: (re, im)

void  F2_construct_I(BNField2 *p, CBigInt re); // BNField2 constructor with imaginary part = 0

void F2_assign(BNField2 *b, BNField2 p); // Assignment: b = p

void F2_add(BNField2 *p, BNField2 b1, BNField2 b2); // Addition of two BNField2 elements

void  F2_add_I(BNField2 *p, BNField2 b, CBigInt k); // Add integer to BNField2

void CBigInt_substract(CBigInt *x, CBigInt a, CBigInt b); // Calculate (a-b) mod p

void  F2_substract(BNField2 *p, BNField2 b1, BNField2 b2); // Subtraction of two BNField2 elements

void  F2_substract_I(BNField2 *p, BNField2 b, CBigInt k); // Subtract integer from BNField2

int F2_isZero(BNField2 b); // Return 1 if element is zero, otherwise return 0

int F2_isOne(BNField2 b); // Return 1 if element is one, otherwise return 0

int F2_equal(BNField2 b1, BNField2 b2); // Compare two elements, return 1 if equal, otherwise return 0

void CBigInt_neg(CBigInt *p, CBigInt a); // Negate CBigInt: p = -a mod p

void F2_negate(BNField2 *p, BNField2 b); // Negation of BNField2 element

void  F2_frobenius(BNField2 *p, BNField2 b); // Frobenius map on BNField2

void  F2_GFrobenius(BNField2 *p, BNField2 b, unsigned int e); // Generalized Frobenius map on BNField2

void  F2_multiply(BNField2 *p, BNField2 b1, BNField2 b2); // (a+bu)(a'+b'u) = (aa'-2bb')+((a+b)(a'+b')-aa'-bb')u

void  F2_multiply_I(BNField2 *p, BNField2 b, CBigInt k); // Multiply by CBigInt: (a+bu)k = ka+kbu

void  F2_multiply_i(BNField2 *p, BNField2 b, int k); // Multiply by small integer: (a+bu)k = ka+kbu

void  F2_multiply_u(BNField2 *p, BNField2 b); // Multiply by u: (a+bu)u = -2b+au

void  F2_square(BNField2 *p, BNField2 b); // Square: (a+bu)^2 = a^2-2b^2+2abu

void  F2_inverse(BNField2 *p, BNField2 b); // Inverse: (a+bu)^(-1) = (a-bu)/(a^2+2b^2)

void F2_toString(BNField2 b, unsigned int system); // Print BNField2 in base 10 or 16

void F2_normorlize(BNField2 *b, BNField2 p); // Normalization

#endif

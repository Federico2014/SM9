#ifndef BNPOINT2_H
#define BNPOINT2_H

#include <stdio.h>
#include "sm9/curve/point.h"

typedef struct
{
	BNField2 x;
	BNField2 y;
	BNField2 z;
}BNPoint2;


void BNPoint2_init(BNPoint2 *p); // BNPoint2 initialization

void P2_construct(BNPoint2 *p, BNField2 x, BNField2 y, BNField2 z); // BNPoint2 constructor

void P2_construct_xy(BNPoint2 *p, BNField2 x, BNField2 y); // BNPoint2 constructor from x, y coordinates

void P2_assign(BNPoint2 *p, BNPoint2 b); // Assignment: p = b

int P2_isZero(BNPoint2 p); // Return 1 if BNPoint2 is zero, otherwise return 0

void  P2_normorlize(BNPoint2 *p, BNPoint2 b); // Normalization in Jacobian coordinates: x = X/Z^2, y = Y/Z^3

int P2_isNormal(BNPoint2 p); // Check if BNPoint is normalized, return 1 if normalized, otherwise return 0

int P2_equal(BNPoint2 p1, BNPoint2 p2); // Compare two points, return 1 if equal, otherwise return 0

void  P2_negate(BNPoint2 *p, BNPoint2 b); // Negation of BNPoint2

void P2_add(BNPoint2 *p, BNPoint2 p1, BNPoint2 p2); // Point addition: p = p1 + p2

void P2_twice(BNPoint2 *p, BNPoint2 q); // Point doubling: p = 2*q

void P2_multiply(BNPoint2 *p, BNPoint2 q, CBigInt k); // Scalar multiplication: p = k*q

int P2_isOnBNTCurve(BNPoint2 p); // Check if point is on BN twist curve y^2 = x^3 + 5u*z^6

void P2_frobenius(BNPoint2 *p, BNPoint2 q); // Frobenius map on BNPoint2

void P2_toString_d(BNPoint2 p,unsigned int system); // Print BNPoint2

void P2_toString(BNPoint2 p,unsigned int system); // Print BNPoint2 in decimal or hexadecimal

#endif

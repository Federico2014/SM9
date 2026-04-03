#ifndef BNPOINT_H
#define BNPOINT_H

#include <stdio.h>
#include "sm9/core/field12.h"

typedef struct
{
	CBigInt x;
	CBigInt y;
	CBigInt z;
}BNPoint;


void BNPoint_init(BNPoint *p); // BNPoint initialization

void P_construct(BNPoint *p, CBigInt x, CBigInt y, CBigInt z); // BNPoint constructor

void P_construct_xy(BNPoint *p, CBigInt x, CBigInt y); // BNPoint constructor from x, y coordinates

void P_assign(BNPoint *p, BNPoint b); // Assignment: p = b

int P_isZero(BNPoint p); // Return 1 if BNPoint is zero, otherwise return 0

/*
  Normalization in Jacobian coordinates
  x = X/Z^2, y = Y/Z^3
 */
void  P_normorlize(BNPoint *p, BNPoint b);

int P_isNormal(BNPoint p);  // Check if BNPoint is normalized, return 1 if normalized, otherwise return 0

int P_equal(BNPoint p1, BNPoint p2);   // Compare two points, return 1 if equal, otherwise return 0

void P_negate(BNPoint *p, BNPoint b);  // Negation: P = (x,y,z), -P = (x,-y,z)

void P_add(BNPoint *p, BNPoint p1, BNPoint p2); // Point addition: *p = p1 + p2

void P_twice(BNPoint *p, BNPoint q);   // Point doubling: *p = 2*q

void P_multiply(BNPoint *p, BNPoint q, CBigInt k); // Scalar multiplication: *p = k*q, k must be greater than 0

int P_isOnBNCurve(BNPoint p); // Check if point is on BN curve y^2 = x^3 + 5*z^6

void P_toString(BNPoint p,unsigned int system);  // Print BNPoint in specified base

#endif

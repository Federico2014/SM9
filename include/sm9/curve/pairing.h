#ifndef BNPAIRING_H
#define BNPAIRING_H

#include "sm9/curve/point2.h"


void Line_Funtion(BNField12 *f, BNPoint2 T, BNPoint2 Q, BNPoint P); // Line function calculation

void Final_exp(BNField12 *f, BNField12 p); // Final exponentiation: f = p^((p^12-1)/12)

void Pairing_opt(BNField12 *f, BNPoint2 Q, BNPoint P); // Optimal pairing calculation

void Pairing_Rate(BNField12 *f, BNPoint2 Q, BNPoint P); // R-ate pairing calculation

#endif

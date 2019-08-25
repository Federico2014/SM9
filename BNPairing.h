#include "BNPoint2.h"


void Line_Funtion(BNField12 *f, BNPoint2 T, BNPoint2 Q, BNPoint P); // 线函数的计算 

void Final_exp(BNField12 *f, BNField12 p); //最终幂的计算 f = b^((b^12-1)/12)

void Pairing_opt(BNField12 *f,BNPoint2 Q, BNPoint P); //最优对的计算

void Pairing_Rate(BNField12 *f, BNPoint2 Q, BNPoint P); // Rate 对的计算
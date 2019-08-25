#include <stdio.h>
#include "BNPoint.h"

typedef struct
{
	BNField2 x;
	BNField2 y;
	BNField2 z;
}BNPoint2;


void BNPoint2_init(BNPoint2 *p); //BNPoint2 初始化  

void P2_construct(BNPoint2 *p, BNField2 x, BNField2 y, BNField2 z); // BNPoint2 构造函数  

void P2_construct_xy(BNPoint2 *p, BNField2 x, BNField2 y); // BNPoint2 构造函数  

void P2_assign(BNPoint2 *p, BNPoint2 b); // 赋值函数 p = b

int P2_isZero(BNPoint2 p); // 若BNPoint2为0,则返回1，否则返加0；

void  P2_normorlize(BNPoint2 *p, BNPoint2 b); // Jacobian坐标系下的规约处理:  x = X/Z^2, y = Y/Z^3

int P2_isNormal(BNPoint2 p); // 判断BNPoint是否为规范类型，若是返加1，否则返回0；

int P2_equal(BNPoint2 p1, BNPoint2 p2); // 若两个域元素相等,则返回1，否则返加0；

void  P2_negate(BNPoint2 *p, BNPoint2 b); //    BNPoint2的负值；

void P2_add(BNPoint2 *p, BNPoint2 p1, BNPoint2 p2); // BNPoint2: p = p1 + p2；

void P2_twice(BNPoint2 *p, BNPoint2 q); // BNPoint: p = 2*q；

void P2_multiply(BNPoint2 *p, BNPoint2 q, CBigInt k); //  计算 BNPoint: p = k*q；

int P2_isOnBNTCurve(BNPoint2 p); // 判断点是否在BN扭曲线y^2 = x^3 + 5u z^6

void P2_frobenius(BNPoint2 *p, BNPoint2 q); //  BNPoint2: Frobeniuse 计算

void P2_toString_d(BNPoint2 p,unsigned int system); // 打印显示BNPoint；

void P2_toString(BNPoint2 p,unsigned int system); // 十六进制或十进制打印显示BNPoint2；
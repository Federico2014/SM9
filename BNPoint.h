#include <stdio.h>
#include "BNField12.h"

typedef struct
{
	CBigInt x;
	CBigInt y;
	CBigInt z;
}BNPoint;


void BNPoint_init(BNPoint *p); //BNPoint 初始化 

void P_construct(BNPoint *p, CBigInt x, CBigInt y, CBigInt z); //BNPoint 构造函数

void P_construct_xy(BNPoint *p, CBigInt x, CBigInt y); //BNPoint 构造函数 

void P_assign(BNPoint *p, BNPoint b); //赋值函数 p = b

int P_isZero(BNPoint p); //若BNPoint为0,则返回1，否则返加0；

/*
  Jacobian坐标系下的规约处理
  x = X/Z^2, y = Y/Z^3
 */
void  P_normorlize(BNPoint *p, BNPoint b);

int P_isNormal(BNPoint p);  //判断BNPoint是否为规范类型，若是返加1，否则返回0；

int P_equal(BNPoint p1, BNPoint p2);   // 若两个域元素相等,则返回1，否则返加0；

void P_negate(BNPoint *p, BNPoint b);  // BNPoint的负值: P = (x,y,z),   -P = (x,-y,z)

void P_add(BNPoint *p, BNPoint p1, BNPoint p2); //  BNPoint: *p = p1 + p2；

void P_twice(BNPoint *p, BNPoint q);   //BNPoint: *p = 2*q；

void P_multiply(BNPoint *p, BNPoint q, CBigInt k); //计算 BNPoint: *p = k*q, k为大于等于0的正整数

int P_isOnBNCurve(BNPoint p); // 判断点是否在BN曲线y^2 = x^3 + 5 z^6

void P_toString(BNPoint p,unsigned int system);  //打印显示BNPoint；


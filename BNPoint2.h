#include <stdio.h>
#include "BNPoint.h"

typedef struct
{
	BNField2 x;
	BNField2 y;
	BNField2 z;
}BNPoint2;


void BNPoint2_init(BNPoint2 *p); //BNPoint2 ��ʼ��  

void P2_construct(BNPoint2 *p, BNField2 x, BNField2 y, BNField2 z); // BNPoint2 ���캯��  

void P2_construct_xy(BNPoint2 *p, BNField2 x, BNField2 y); // BNPoint2 ���캯��  

void P2_assign(BNPoint2 *p, BNPoint2 b); // ��ֵ���� p = b

int P2_isZero(BNPoint2 p); // ��BNPoint2Ϊ0,�򷵻�1�����򷵼�0��

void  P2_normorlize(BNPoint2 *p, BNPoint2 b); // Jacobian����ϵ�µĹ�Լ����:  x = X/Z^2, y = Y/Z^3

int P2_isNormal(BNPoint2 p); // �ж�BNPoint�Ƿ�Ϊ�淶���ͣ����Ƿ���1�����򷵻�0��

int P2_equal(BNPoint2 p1, BNPoint2 p2); // ��������Ԫ�����,�򷵻�1�����򷵼�0��

void  P2_negate(BNPoint2 *p, BNPoint2 b); //    BNPoint2�ĸ�ֵ��

void P2_add(BNPoint2 *p, BNPoint2 p1, BNPoint2 p2); // BNPoint2: p = p1 + p2��

void P2_twice(BNPoint2 *p, BNPoint2 q); // BNPoint: p = 2*q��

void P2_multiply(BNPoint2 *p, BNPoint2 q, CBigInt k); //  ���� BNPoint: p = k*q��

int P2_isOnBNTCurve(BNPoint2 p); // �жϵ��Ƿ���BNŤ����y^2 = x^3 + 5u z^6

void P2_frobenius(BNPoint2 *p, BNPoint2 q); //  BNPoint2: Frobeniuse ����

void P2_toString_d(BNPoint2 p,unsigned int system); // ��ӡ��ʾBNPoint��

void P2_toString(BNPoint2 p,unsigned int system); // ʮ�����ƻ�ʮ���ƴ�ӡ��ʾBNPoint2��
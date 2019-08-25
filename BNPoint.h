#include <stdio.h>
#include "BNField12.h"

typedef struct
{
	CBigInt x;
	CBigInt y;
	CBigInt z;
}BNPoint;


void BNPoint_init(BNPoint *p); //BNPoint ��ʼ�� 

void P_construct(BNPoint *p, CBigInt x, CBigInt y, CBigInt z); //BNPoint ���캯��

void P_construct_xy(BNPoint *p, CBigInt x, CBigInt y); //BNPoint ���캯�� 

void P_assign(BNPoint *p, BNPoint b); //��ֵ���� p = b

int P_isZero(BNPoint p); //��BNPointΪ0,�򷵻�1�����򷵼�0��

/*
  Jacobian����ϵ�µĹ�Լ����
  x = X/Z^2, y = Y/Z^3
 */
void  P_normorlize(BNPoint *p, BNPoint b);

int P_isNormal(BNPoint p);  //�ж�BNPoint�Ƿ�Ϊ�淶���ͣ����Ƿ���1�����򷵻�0��

int P_equal(BNPoint p1, BNPoint p2);   // ��������Ԫ�����,�򷵻�1�����򷵼�0��

void P_negate(BNPoint *p, BNPoint b);  // BNPoint�ĸ�ֵ: P = (x,y,z),   -P = (x,-y,z)

void P_add(BNPoint *p, BNPoint p1, BNPoint p2); //  BNPoint: *p = p1 + p2��

void P_twice(BNPoint *p, BNPoint q);   //BNPoint: *p = 2*q��

void P_multiply(BNPoint *p, BNPoint q, CBigInt k); //���� BNPoint: *p = k*q, kΪ���ڵ���0��������

int P_isOnBNCurve(BNPoint p); // �жϵ��Ƿ���BN����y^2 = x^3 + 5 z^6

void P_toString(BNPoint p,unsigned int system);  //��ӡ��ʾBNPoint��


#include "BNField2.h"


typedef struct
{
    BNField2 re;
	BNField2 im;
} BNField4;


void BNField4_init(BNField4 *p); // ��ʼ��  

void F4_construct(BNField4 *p, BNField2 re, BNField2 im); //�Ĵ�����Ĺ��캯�� 

void F4_normorlize(BNField4 *p, BNField4 b); // ��Լ������

void F4_construct_F2(BNField4 *p, BNField2 re); // �Ĵ�����Ĺ��캯��,�鲿Ϊ0  

void F4_assign(BNField4 *p, BNField4 b);  //  ��ֵ����p=b 

void  F4_add( BNField4 *p, BNField4 b1, BNField4 b2); //���Ĵ�����Ԫ�����

void  F4_add_F2(BNField4 *p, BNField4 b, BNField2 k); //�Ͷ�������Ԫ�����

void  F4_substract(BNField4 *p, BNField4 b1, BNField4 b2); //�Ĵ�����Ԫ�����

void  F4_substract_F2(BNField4 *p, BNField4 b, BNField2 k);//�Ĵ�����Ԫ�ؼ�ȥһ����������Ԫ��  
 
int F4_isZero(BNField4 b); //����Ԫ��Ϊ0,�򷵻�1�����򷵼�0��

int F4_isOne(BNField4 b);//����Ԫ��Ϊ1,�򷵻�1�����򷵼�0��

int F4_equal(BNField4 b1, BNField4 b2); //��������Ԫ�����,�򷵻�1�����򷵼�0��

void  F4_negate(BNField4 *p, BNField4 b); //��Ԫ�صĸ�ֵ��

void F4_frobenius(BNField4 *p, BNField4 b);//��Ԫ�ص�Frobeniusֵ��

void  F4_GFrobenius(BNField4 *p, BNField4 b, unsigned int e);//�Ĵ���Ԫ�صĹ���Frobeniusֵ��

void  F4_multiply(BNField4 *p, BNField4 b1, BNField4 b2); // (a+bv)(a'+b'v) =(aa'+bb'u)+((a+b)(a'+b')-aa'-bb')v

void  F4_multiply_F2(BNField4 *p, BNField4 b, BNField2 k); //���Զ�������Ԫ��  (a+bu)k = ka+kbu

void  F4_multiply_i(BNField4 *p, BNField4 b, int k); //  ����С�� (a+bu)k = ka+kbu

void  F4_multiply_I(BNField4 *p, BNField4 b, CBigInt k);// ���Դ���  (a+bu)k  = ka+kbu

void  F4_multiply_v(BNField4 *p, BNField4 b); //  ����v (a+bv)v = bu+av

void  F4_square(BNField4 *p, BNField4 b); //�Ĵ�����Ԫ�ص�ƽ������  (a+bv)^2=a^2+2abv+b^2 u^4  = a^2+b^2u+2abv

void  F4_inverse(BNField4 *p, BNField4 b); // �Ĵ�����Ԫ�ص�������  (a+bv)^(-1)=(a-bv)/(a^2-b^2 ^2 )=(a-bv)/(a^2-b^2u)

void F4_toString(BNField4 b,unsigned int system);//��ʾ�Ĵ�����Ԫ��




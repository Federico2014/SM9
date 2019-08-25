#include "Params.h"


typedef struct 
{
    CBigInt re;
	CBigInt im;

}BNField2;


void BNField2_init(BNField2 *p); //��ʼ��

void F2_construct(BNField2 *p, CBigInt re, CBigInt im);//��������Ĺ��캯�� 

void  F2_construct_I(BNField2 *p, CBigInt re);//��������Ĺ��캯��,�鲿Ϊ0  

void F2_assign(BNField2 *b, BNField2 p);//��ֵ����b=p 

void F2_add(BNField2 *p, BNField2 b1, BNField2 b2);//�Ͷ�������Ԫ�����

void  F2_add_I(BNField2 *p, BNField2 b, CBigInt k);//��������� 

void CBigInt_substract(CBigInt *x, CBigInt a, CBigInt b);//���أ�a-b��mod p

void  F2_substract(BNField2 *p, BNField2 b1, BNField2 b2);//��������Ԫ�����

void  F2_substract_I(BNField2 *p, BNField2 b, CBigInt k);//��������Ԫ�ؼ�ȥһ�������� 

int F2_isZero(BNField2 b);//����Ԫ��Ϊ0,�򷵻�1�����򷵼�0��

int F2_isOne(BNField2 b);//����Ԫ��Ϊ1,�򷵻�1�����򷵼�0��

int F2_equal(BNField2 b1, BNField2 b2);//��������Ԫ�����,�򷵻�1�����򷵼�0��

void CBigInt_neg(CBigInt *p, CBigInt a);//����CBigInt�ĸ�ֵ������-a��mod p

void F2_negate(BNField2 *p, BNField2 b);//��Ԫ�صĸ�ֵ��

void  F2_frobenius(BNField2 *p, BNField2 b);//��Ԫ�ص�Frobeniusֵ��

void  F2_GFrobenius(BNField2 *p, BNField2 b, unsigned int e); //��Ԫ�صĹ���Frobeniusֵ��

void  F2_multiply(BNField2 *p, BNField2 b1,BNField2 b2); //(a+bu)(a'+b'u)  =  (aa'-2bb')+((a+b)(a'+b')-aa'-bb')u

void  F2_multiply_I(BNField2 *p, BNField2 b, CBigInt k);//���Դ��� (a+bu)k  = ka+kbu

void  F2_multiply_i(BNField2 *p, BNField2 b, int k);//����С��  (a+bu)k = ka+kbu

void  F2_multiply_u(BNField2 *p, BNField2 b);//����u (a+bu)u = -2b+au

void  F2_square(BNField2 *p, BNField2 b);//��������Ԫ�ص�ƽ������   (a+bu)^2=a^2+2abu+b^2 u^2 = a^2-2b^2+2abu

void  F2_inverse(BNField2 *p, BNField2 b);//��������Ԫ�ص������� (a+bu)^(-1)=(a-bu)/(a^2-b^2 u^2 )=(a-bu)/(a^2+2b^2 )

void F2_toString(BNField2 b,unsigned int system);//��ʾ��������Ԫ��:  ��10���ƻ�16���Ƹ�ʽ������ַ���

void F2_normorlize(BNField2 *b, BNField2 p); // ��Լ������

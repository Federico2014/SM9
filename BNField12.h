#include "BNField4.h"


typedef struct
{
    BNField4 re;
	BNField4 im;
	BNField4 sq;
}BNField12;


void BNField12_init(BNField12 *p); //��ʼ��  

void F12_construct(BNField12 *p,BNField4 re, BNField4 im, BNField4 sq); //ʮ��������Ĺ��캯��  

void F12_normorlize(BNField12 *p,BNField12 b);  //��Լ������

void  F12_assign(BNField12 *p,BNField12 b);  //��ֵ���� p=b 

void  F12_assign_1(BNField12 *p); //��ֵ����p=1 

void  F12_add(BNField12 *p,BNField12 b1, BNField12 b2); //��ʮ��������Ԫ����� 

void  F12_add_F4(BNField12 *p,BNField12 b, BNField4 k); // ���Ĵδ�����Ԫ�����

void  F12_substract(BNField12 *p, BNField12 b1, BNField12 b2); //ʮ��������Ԫ�����  

void  F12_substract_F4(BNField12 *p,BNField12 b, BNField4 k); //ʮ��������Ԫ�ؼ�ȥһ���Ĵ�����Ԫ��  

int F12_isZero(BNField12 b); //��12������Ԫ��Ϊ0,�򷵻�1�����򷵼�0��

int F12_isOne(BNField12 b); //  ��12������Ԫ��Ϊ1,�򷵻�1�����򷵼�0��

int F12_equal(BNField12 b1, BNField12 b2); // ������12������Ԫ�����,�򷵻�1�����򷵼�0��

void  F12_negate(BNField12 *p,BNField12 b); // 12������Ԫ�صĸ�ֵ��

void  F12_frobenius(BNField12 *p,BNField12 b); //  ʮ��������Ԫ�ص�Frobeniusֵ��

void  F12_GFrobenius(BNField12 *p,BNField12 b, unsigned int e); //ʮ��������Ԫ�صĹ���Frobeniusֵ��

/*
   (a+bw+cw^2)(a'+b'w+c'w^2)  ��
       =aa'+((b+c)(b'+c')-bb'-cc')v+((a+b)(a'+b')-aa'-bb'+cc'v)w
	           + ((a+c)(a'+c')-aa'-cc'+bb')w^2
 */
void  F12_multiply(BNField12 *p,BNField12 b1, BNField12 b2);

void  F12_multiply_F4(BNField12 *p, BNField12 b, BNField4 k); //�����Ĵ�����Ԫ�� (a+bw+cw^2)k = ka+kbw+kcw^2

void  F12_multiply_i(BNField12 *p,BNField12 b, int k); // ����С�� (a+bw+cw^2)k = ka+kbw+kcw^2

void  F12_multiply_I(BNField12 *p, BNField12 b, CBigInt k); //���Դ���  (a+bw+cw^2)k = ka+kbw+kcw^2

/*
   ʮ��������Ԫ�ص�ƽ������
   (a+bw+cw^2)^2  ��
       =a^2+((b+c)^2-b^2-c^2)v+((a+b)^2-a^2-b^2+c^2 v)w
	           + ((a+c)^2-a^2-c^2+b^2)w^2
 */
void  F12_square(BNField12 *p, BNField12 b);


/*
   ʮ��������Ԫ�ص�������
 (a+bw+cw^2)^(-1)=(A+Bw+Cw^2)/(bCv+aA+cBv)
 ���� A = a^2-bcv
      B = c^2 v-ab
	  C = b^2-ac
 */
void  F12_inverse(BNField12 *p, BNField12 b);

void F12_exp(BNField12 *p, BNField12 b, CBigInt e); //���� *p = b^e��eΪ���ڻ����0�������� 

void F12_toString_d(BNField12 b,unsigned int system); // ��һ����ʽ��ʾʮ��������Ԫ��

void F12_toString(BNField12 b,unsigned int system); //����SM9��׼����ʮ������ʮ������ʾʮ��������Ԫ��

 
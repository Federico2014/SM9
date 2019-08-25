#include "Params.h"


typedef struct 
{
    CBigInt re;
	CBigInt im;

}BNField2;


void BNField2_init(BNField2 *p); //初始化

void F2_construct(BNField2 *p, CBigInt re, CBigInt im);//二次扩域的构造函数 

void  F2_construct_I(BNField2 *p, CBigInt re);//二次扩域的构造函数,虚部为0  

void F2_assign(BNField2 *b, BNField2 p);//赋值函数b=p 

void F2_add(BNField2 *p, BNField2 b1, BNField2 b2);//和二次扩域元素相加

void  F2_add_I(BNField2 *p, BNField2 b, CBigInt k);//和整数相加 

void CBigInt_substract(CBigInt *x, CBigInt a, CBigInt b);//返回（a-b）mod p

void  F2_substract(BNField2 *p, BNField2 b1, BNField2 b2);//二次扩域元素相减

void  F2_substract_I(BNField2 *p, BNField2 b, CBigInt k);//二次扩域元素减去一个正整数 

int F2_isZero(BNField2 b);//若域元素为0,则返回1，否则返加0；

int F2_isOne(BNField2 b);//若域元素为1,则返回1，否则返加0；

int F2_equal(BNField2 b1, BNField2 b2);//若两个域元素相等,则返回1，否则返加0；

void CBigInt_neg(CBigInt *p, CBigInt a);//计算CBigInt的负值，即（-a）mod p

void F2_negate(BNField2 *p, BNField2 b);//域元素的负值；

void  F2_frobenius(BNField2 *p, BNField2 b);//域元素的Frobenius值；

void  F2_GFrobenius(BNField2 *p, BNField2 b, unsigned int e); //域元素的广义Frobenius值；

void  F2_multiply(BNField2 *p, BNField2 b1,BNField2 b2); //(a+bu)(a'+b'u)  =  (aa'-2bb')+((a+b)(a'+b')-aa'-bb')u

void  F2_multiply_I(BNField2 *p, BNField2 b, CBigInt k);//乘以大数 (a+bu)k  = ka+kbu

void  F2_multiply_i(BNField2 *p, BNField2 b, int k);//乘以小数  (a+bu)k = ka+kbu

void  F2_multiply_u(BNField2 *p, BNField2 b);//乘以u (a+bu)u = -2b+au

void  F2_square(BNField2 *p, BNField2 b);//二次扩域元素的平方运算   (a+bu)^2=a^2+2abu+b^2 u^2 = a^2-2b^2+2abu

void  F2_inverse(BNField2 *p, BNField2 b);//二次扩域元素的逆运算 (a+bu)^(-1)=(a-bu)/(a^2-b^2 u^2 )=(a-bu)/(a^2+2b^2 )

void F2_toString(BNField2 b,unsigned int system);//显示二次扩域元素:  按10进制或16进制格式输出到字符串

void F2_normorlize(BNField2 *b, BNField2 p); // 规约化处理

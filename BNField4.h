#include "BNField2.h"


typedef struct
{
    BNField2 re;
	BNField2 im;
} BNField4;


void BNField4_init(BNField4 *p); // 初始化  

void F4_construct(BNField4 *p, BNField2 re, BNField2 im); //四次扩域的构造函数 

void F4_normorlize(BNField4 *p, BNField4 b); // 规约化处理

void F4_construct_F2(BNField4 *p, BNField2 re); // 四次扩域的构造函数,虚部为0  

void F4_assign(BNField4 *p, BNField4 b);  //  赋值函数p=b 

void  F4_add( BNField4 *p, BNField4 b1, BNField4 b2); //和四次扩域元素相加

void  F4_add_F2(BNField4 *p, BNField4 b, BNField2 k); //和二次扩域元素相加

void  F4_substract(BNField4 *p, BNField4 b1, BNField4 b2); //四次扩域元素相减

void  F4_substract_F2(BNField4 *p, BNField4 b, BNField2 k);//四次扩域元素减去一个二次扩域元素  
 
int F4_isZero(BNField4 b); //若域元素为0,则返回1，否则返加0；

int F4_isOne(BNField4 b);//若域元素为1,则返回1，否则返加0；

int F4_equal(BNField4 b1, BNField4 b2); //若两个域元素相等,则返回1，否则返加0；

void  F4_negate(BNField4 *p, BNField4 b); //域元素的负值；

void F4_frobenius(BNField4 *p, BNField4 b);//域元素的Frobenius值；

void  F4_GFrobenius(BNField4 *p, BNField4 b, unsigned int e);//四次域元素的广义Frobenius值；

void  F4_multiply(BNField4 *p, BNField4 b1, BNField4 b2); // (a+bv)(a'+b'v) =(aa'+bb'u)+((a+b)(a'+b')-aa'-bb')v

void  F4_multiply_F2(BNField4 *p, BNField4 b, BNField2 k); //乘以二次扩域元素  (a+bu)k = ka+kbu

void  F4_multiply_i(BNField4 *p, BNField4 b, int k); //  乘以小数 (a+bu)k = ka+kbu

void  F4_multiply_I(BNField4 *p, BNField4 b, CBigInt k);// 乘以大数  (a+bu)k  = ka+kbu

void  F4_multiply_v(BNField4 *p, BNField4 b); //  乘以v (a+bv)v = bu+av

void  F4_square(BNField4 *p, BNField4 b); //四次扩域元素的平方运算  (a+bv)^2=a^2+2abv+b^2 u^4  = a^2+b^2u+2abv

void  F4_inverse(BNField4 *p, BNField4 b); // 四次扩域元素的逆运算  (a+bv)^(-1)=(a-bv)/(a^2-b^2 ^2 )=(a-bv)/(a^2-b^2u)

void F4_toString(BNField4 b,unsigned int system);//显示四次扩域元素




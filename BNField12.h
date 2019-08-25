#include "BNField4.h"


typedef struct
{
    BNField4 re;
	BNField4 im;
	BNField4 sq;
}BNField12;


void BNField12_init(BNField12 *p); //初始化  

void F12_construct(BNField12 *p,BNField4 re, BNField4 im, BNField4 sq); //十二次扩域的构造函数  

void F12_normorlize(BNField12 *p,BNField12 b);  //规约化处理

void  F12_assign(BNField12 *p,BNField12 b);  //赋值函数 p=b 

void  F12_assign_1(BNField12 *p); //赋值函数p=1 

void  F12_add(BNField12 *p,BNField12 b1, BNField12 b2); //和十二次扩域元素相加 

void  F12_add_F4(BNField12 *p,BNField12 b, BNField4 k); // 和四次次扩域元素相加

void  F12_substract(BNField12 *p, BNField12 b1, BNField12 b2); //十二次扩域元素相减  

void  F12_substract_F4(BNField12 *p,BNField12 b, BNField4 k); //十二次扩域元素减去一个四次扩域元素  

int F12_isZero(BNField12 b); //若12次扩域元素为0,则返回1，否则返加0；

int F12_isOne(BNField12 b); //  若12次扩域元素为1,则返回1，否则返加0；

int F12_equal(BNField12 b1, BNField12 b2); // 若两个12次扩域元素相等,则返回1，否则返加0；

void  F12_negate(BNField12 *p,BNField12 b); // 12次扩域元素的负值；

void  F12_frobenius(BNField12 *p,BNField12 b); //  十二次扩域元素的Frobenius值；

void  F12_GFrobenius(BNField12 *p,BNField12 b, unsigned int e); //十二次扩域元素的广义Frobenius值；

/*
   (a+bw+cw^2)(a'+b'w+c'w^2)  ；
       =aa'+((b+c)(b'+c')-bb'-cc')v+((a+b)(a'+b')-aa'-bb'+cc'v)w
	           + ((a+c)(a'+c')-aa'-cc'+bb')w^2
 */
void  F12_multiply(BNField12 *p,BNField12 b1, BNField12 b2);

void  F12_multiply_F4(BNField12 *p, BNField12 b, BNField4 k); //乘以四次扩域元素 (a+bw+cw^2)k = ka+kbw+kcw^2

void  F12_multiply_i(BNField12 *p,BNField12 b, int k); // 乘以小数 (a+bw+cw^2)k = ka+kbw+kcw^2

void  F12_multiply_I(BNField12 *p, BNField12 b, CBigInt k); //乘以大数  (a+bw+cw^2)k = ka+kbw+kcw^2

/*
   十二次扩域元素的平方运算
   (a+bw+cw^2)^2  ；
       =a^2+((b+c)^2-b^2-c^2)v+((a+b)^2-a^2-b^2+c^2 v)w
	           + ((a+c)^2-a^2-c^2+b^2)w^2
 */
void  F12_square(BNField12 *p, BNField12 b);


/*
   十二次扩域元素的逆运算
 (a+bw+cw^2)^(-1)=(A+Bw+Cw^2)/(bCv+aA+cBv)
 其中 A = a^2-bcv
      B = c^2 v-ab
	  C = b^2-ac
 */
void  F12_inverse(BNField12 *p, BNField12 b);

void F12_exp(BNField12 *p, BNField12 b, CBigInt e); //计算 *p = b^e，e为大于或等于0的正整数 

void F12_toString_d(BNField12 b,unsigned int system); // 以一般形式显示十二次扩域元素

void F12_toString(BNField12 b,unsigned int system); //根据SM9标准，以十六进或十进制显示十二次扩域元素

 
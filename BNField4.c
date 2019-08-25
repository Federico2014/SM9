# include "BNField4.h"
# include <stdio.h>

/*
   初始化  

 */
void BNField4_init(BNField4 *b)
{
	BNField2_init(&b->re);
	BNField2_init(&b->im);	
}


/*
   四次扩域的构造函数  

 */
 void F4_construct(BNField4 *b, BNField2 re, BNField2 im)
{
	
	F2_assign(&b->re,re);
	F2_assign(&b->im,im);
}

/*
  规约化处理
 */
void F4_normorlize(BNField4 *p, BNField4 b)
{   
	F2_normorlize(&p->re,b.re);
	F2_normorlize(&p->im,b.im);
}

/*
   四次扩域的构造函数,虚部为0  

 */
void F4_construct_F2(BNField4 *b,BNField2 re)
{	
	F2_construct(&b->im,BN.ZERO,BN.ZERO);
	F2_assign(&b->re,re);
}

/*
  赋值函数p=b 
 */
void F4_assign(BNField4 *p, BNField4 b)
{   
	F2_assign(&p->re,b.re);
    F2_assign(&p->im,b.im);
}

/*
   和四次扩域元素相加
 */
void  F4_add(BNField4 *b3, BNField4 b1, BNField4 b2)
{    
	F2_add(&b3->re,b1.re,b2.re);
	F2_add(&b3->im,b1.im,b2.im);
}


/*
   和二次扩域元素相加  
 */
void F4_add_F2(BNField4 *p, BNField4 b, BNField2 k)
{
    
	F2_add(&p->re,b.re,k);
	F2_assign(&p->im,b.im);
}

/*
   四次扩域元素相减  
 */
void F4_substract(BNField4 *b3, BNField4 b1, BNField4 b2)
{	
	F2_substract(&b3->re,b1.re,b2.re);
	F2_substract(&b3->im,b1.im,b2.im);
}

/*
   四次扩域元素减去一个二次扩域元素  
*/
 void  F4_substract_F2(BNField4 *p, BNField4 b, BNField2 k)
 {	 
	 F2_substract(&p->re,b.re,k);
	 F2_assign(&p->im,b.im);
 }
 
/*
   若域元素为0,则返回1，否则返加0；
 */
int F4_isZero(BNField4 b)
{
	return F2_isZero(b.re) && F2_isZero(b.im);
}

/*
   若域元素为1,则返回1，否则返加0；

 */
int F4_isOne(BNField4 b)
{
	return F2_isOne(b.re) && F2_isZero(b.im);
}

/*
   若两个域元素相等,则返回1，否则返加0；

 */
int F4_equal(BNField4 b1, BNField4 b2)
{
	return F2_equal(b1.re,b2.re) && F2_equal(b1.im,b2.im);
}

/*
   域元素的负值；
 */
void F4_negate(BNField4 *p, BNField4 b)
{
	
	F2_negate(&p->re,b.re);
	F2_negate(&p->im,b.im);
}

/*
   域元素的Frobenius值；

 */
void F4_frobenius(BNField4 *p,BNField4 b)
{	
	F2_frobenius(&p->im,b.im);
	F2_multiply_I(&p->im,p->im,BN.exp__8);
	F2_frobenius(&p->re,b.re);
}

/*
   四次域元素的广义Frobenius值；

 */
void  F4_GFrobenius(BNField4 *p, BNField4 b, unsigned int e)
{
	
	CBigInt d;
	switch (e)
	{
	  case 2: Get(&d,"82434016654578246444830763105245969129603161266935169637912592173415460324732",DEC);break; //(-8)^((q^2-1)/12) mod q
	  case 3: Get(&d,"33406564957872034372781654663986859928616373163521649277556116081423418160492",DEC);break; //(-8)^((q^3-1)/12) mod q
	  case 6: Get(&d,"82434016654578246444830763105245969129603161266935169637912592173415460324732",DEC); //(-8)^((q^6-1)/12) mod q
	}
	
	F2_GFrobenius(&p->im,b.im,e);
	F2_multiply_I(&p->im,p->im,d);
	F2_GFrobenius(&p->re,b.re,e);
}

/*
   (a+bv)(a'+b'v)  ；
       =(aa'+bb'u)+((a+b)(a'+b')-aa'-bb')v
 */
void  F4_multiply(BNField4 *b3, BNField4 b1, BNField4 b2)
{
    
	BNField2 a,b,c,re,im; 	
	F2_multiply(&a,b1.re,b2.re);
	F2_multiply(&b,b1.im,b2.im);

	F2_multiply_u(&re,b);
	F2_add(&re,a,re);
	F2_add(&im,b1.re,b1.im);	
	F2_add(&c,b2.re,b2.im);	
	F2_multiply(&im,im,c);  //	
	F2_substract(&im,im,a);
	F2_substract(&im,im,b);

 
	F4_construct(b3,re,im);
}


/* 
   乘以二次扩域元素
   (a+bu)k  ；
       =ka+kbu
 */
void F4_multiply_F2(BNField4 *p,BNField4 b, BNField2 k)
{
	
	F2_multiply(&p->re,b.re,k);
	F2_multiply(&p->im,b.im,k);
}

/*
   乘以小数 
   (a+bu)k  ；
       =ka+kbu
 */
void F4_multiply_i(BNField4 *p, BNField4 b, int k)
{    
	F2_multiply_i(&p->re,b.re,k);
	F2_multiply_i(&p->im,b.im,k);
}

/*
   乘以大数 
   (a+bu)k  ；
       =ka+kbu
 */
void F4_multiply_I(BNField4 *p, BNField4 b, CBigInt k)
{
	
	F2_multiply_I(&p->re,b.re,k);
	F2_multiply_I(&p->im,b.im,k);
}

/*
   乘以v 
   (a+bv)v  ；
       =bu+av
 */
void F4_multiply_v(BNField4 *p, BNField4 b)
{
	BNField2 im,re;
	F2_assign(&im,b.im);
	F2_assign(&re,b.re);
	F2_assign(&p->im,re);
	F2_multiply_u(&p->re,im);
}


/*
   四次扩域元素的平方运算
   (a+bv)^2=a^2+2abv+b^2 u^4 
                    =a^2+b^2u+2abv

 */
void F4_square(BNField4 *p, BNField4 b)
{
	
	BNField2 m,re,im;

	F2_square(&re,b.re);
    F2_square(&m,b.im);
	F2_multiply_u(&m,m);
	F2_add(&re,re,m);

	F2_multiply(&im,b.re,b.im);
	F2_add(&im,im,im);
    
	F4_construct(p,re,im);
}


/*
   四次扩域元素的逆运算
 (a+bv)^(-1)=(a-bv)/(a^2-b^2 ^2 )=(a-bv)/(a^2-b^2u)

 */
void F4_inverse( BNField4 *p, BNField4 b)
{
   
	BNField2 m,n;
    F2_square(&m,b.re);
	F2_square(&n,b.im);
    F2_multiply_u(&n,n);

	F2_substract(&m,m,n);
	F2_inverse(&m,m);
	F2_multiply(&p->re,b.re,m);
	F2_multiply(&p->im,b.im,m);
	F2_negate(&p->im,p->im);
}


/*
  显示四次扩域元素
 */
void F4_toString(BNField4 b,unsigned int system)
{
   printf("[(");
   F2_toString(b.im,system);
   printf(") v + (");
   F2_toString(b.re,system);
   printf(")]");
}





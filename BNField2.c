#include "BNField2.h"

/*
   初始化
 */
 void BNField2_init(BNField2 *b)
{    
	CBigIntInit(&b->re);
    CBigIntInit(&b->im);  
}


/*
   二次扩域的构造函数 
*/
void F2_construct(BNField2 *b,CBigInt re, CBigInt im)
{
	 //BNField2 b;
     Mov_Big_Big(&b->re,re);
	 Mov_Big_Big(&b->im,im);
	 if(Cmp(b->re,BN.q)>0)
		 Mod_Big_Big(&b->re,b->re,BN.q);
	 if(Cmp(b->im,BN.q)>=0)
		 Mod_Big_Big(&b->im,b->im,BN.q);	
	
}


/*
   二次扩域的构造函数,虚部为0  
 */
void F2_construct_I(BNField2 *b,CBigInt re)
{	
	Mov_Big_Big(&b->re,re);
	Mov_Big_Long(&b->im,0);
	if(Cmp(b->re,BN.q)>=0)
		Mod_Big_Big(&b->re,b->re,BN.q);	
}

/*
  赋值函数b=p 
 */
void F2_assign(BNField2 *b, BNField2 p)
{     
	Mov_Big_Big(&b->re,p.re);
	Mov_Big_Big(&b->im,p.im);	
}


/*
   和二次扩域元素相加  

 */
void F2_add(BNField2 *b3, BNField2 b1, BNField2 b2)
{
    
	Add_Big_Big(&b3->re,b1.re,b2.re);
	Add_Big_Big(&b3->im,b1.im,b2.im);
	if(Cmp(b3->re,BN.q)>=0 )
		Mod_Big_Big(&b3->re,b3->re,BN.q);
    if(Cmp(b3->im,BN.q)>=0 )
		Mod_Big_Big(&b3->im,b3->im,BN.q);
	//return b3;
}


/*
   和整数相加  
 */
void F2_add_I(BNField2 *p, BNField2 b, CBigInt k)
{
    
	Add_Big_Big(&p->re,b.re,k);
	Mov_Big_Big(&p->im,b.im);
	if(Cmp(p->re,BN.q)>=0 )
		Mod_Big_Big(&p->re,p->re,BN.q);
	//return p;
}

/*
   返回 X = （a-b）mod p
*/
void CBigInt_substract(CBigInt *X, CBigInt a, CBigInt b)
{
	CBigInt c,div;
	if(Cmp(a,b)>=0)
	{
		Sub_Big_Big(&c,a,b);  //
		if(Cmp(c,BN.q)>=0 )
	      Mod_Big_Big(&c,c,BN.q);
	}
    else
	{
		//
		Sub_Big_Big(&c,b,a);		
		Div_Big_Big(&div,c,BN.q);
		Add_Big_Long(&div,div,1);
		Mul_Big_Big(&div,div,BN.q);
		Sub_Big_Big(&c,div,c);
		if(Cmp(c,BN.q)==0)
			Mov_Big_Long(&c,0);
	}

	Mov_Big_Big(X,c);
}


/*
   二次扩域元素相减  
 */
void  F2_substract(BNField2 *b3, BNField2 b1, BNField2 b2)
{
	
	CBigInt_substract(&b3->re,b1.re,b2.re);
	CBigInt_substract(&b3->im,b1.im,b2.im);
}


/*
   二次扩域元素减去一个正整数  
*/
 void  F2_substract_I(BNField2 *p,BNField2 b, CBigInt k)
 {
	 
	 CBigInt_substract(&p->re,b.re,k);
	 Mov_Big_Big(&p->im,b.im);

 }


/*
   若域元素为0,则返回1，否则返加0；

 */
int F2_isZero(BNField2 b)
{
	return Cmp(b.re,BN.ZERO)==0 && Cmp(b.im,BN.ZERO)==0;
}

/*
   若域元素为1,则返回1，否则返加0；

 */
int F2_isOne(BNField2 b)
{
	return Cmp(b.re,BN.ONE)==0 && Cmp(b.im,BN.ZERO)==0;
}

/*
   若两个域元素相等,则返回1，否则返加0；

 */
int F2_equal(BNField2 b1, BNField2 b2)
{
	if (Cmp(b1.re,b2.re)==0 && Cmp(b1.im,b2.im)==0)
		return 1;
	else
		return 0;
}
/*
   计算CBigInt的负值，即（-a）mod p
*/
void CBigInt_neg(CBigInt *p, CBigInt a)
{
	CBigInt_substract(p,BN.ZERO,a);
}

/*
   域元素的负值；
 */
void F2_negate(BNField2 *p,BNField2 b)
{
	
	CBigInt_substract(&p->re,BN.ZERO,b.re);
	CBigInt_substract(&p->im,BN.ZERO,b.im);	
}

/*
   域元素的Frobenius值；

 */
void  F2_frobenius(BNField2 *p,BNField2 b)
{
	
	Mul_Big_Big(&p->im,b.im,BN.exp_64);
	Mov_Big_Big(&p->re,b.re);
	F2_construct(p,p->re,p->im);
}

/*
   域元素的广义Frobenius值；

 */
void F2_GFrobenius(BNField2 *p, BNField2 b, unsigned int e)
{
	
	CBigInt d;
	switch (e)
	{
	  case 2: Get(&d,"1",DEC); break;  // 64^((q^2-1)/12) mod q
	  case 3: Get(&d,"82434016654578246444830763105245969129603161266935169637912592173415460324732",DEC); break;   // 64^((q^3-1)/12) mod q
	  case 6: Get(&d,"1",DEC);        // 64^((q^6-1)/12) mod q
	}
	Mul_Big_Big(&p->im,b.im,d);
	Mov_Big_Big(&p->re,b.re);
	F2_construct(p,p->re,p->im);
}



/*
   (a+bu)(a'+b'u)  ；
       =(aa'-2bb')+((a+b)(a'+b')-aa'-bb')u
 */
void  F2_multiply(BNField2 *b3, BNField2 b1,BNField2 b2)
{   
	CBigInt a,b,c,re,im;
	
	Mul_Big_Big(&a,b1.re,b2.re);
	Mul_Big_Big(&b,b1.im,b2.im);

	Add_Big_Big(&re,b,b);
	CBigInt_substract(&re,a,re);	
	Add_Big_Big(&im,b1.re,b1.im);	
	Add_Big_Big(&c,b2.re,b2.im);
	Mul_Big_Big(&im,im,c);	
	CBigInt_substract(&im,im,a);               //	
	CBigInt_substract(&im,im,b);	
	F2_construct(b3,re,im);
    
  }


/* 
   乘以大数
   (a+bu)k  ；
       =ka+kbu
 */
void  F2_multiply_I(BNField2 *p,BNField2 b, CBigInt k)
{
	CBigInt re,im;
	Mul_Big_Big(&re,b.re,k);
	Mul_Big_Big(&im,b.im,k);
	F2_construct(p,re,im);
}

/*
   乘以小数 
   (a+bu)k  ；
       =ka+kbu
 */
void  F2_multiply_i( BNField2 *b2, BNField2 b, int k)
{	
	Mul_Big_Long(&b2->re,b.re,k);
	Mul_Big_Long(&b2->im,b.im,k);
	F2_construct(b2,b2->re,b2->im);
}


/*
   乘以u 
   (a+bu)u  ；
       =-2b+au
 */
void F2_multiply_u(BNField2 *p, BNField2 b)
{
	CBigInt re,im;

	Add_Big_Big(&re,b.im,b.im);
	CBigInt_neg(&re,re);
	
	Mov_Big_Big(&im,b.re);
	F2_construct(p,re,im);	
}

/*
   二次扩域元素的平方运算
   (a+bu)^2=a^2+2abu+b^2 u^2 
                    =a^2-2b^2+2abu

 */
void  F2_square(BNField2 *p, BNField2 b)
{
	
	CBigInt m,re,im;

	Mul_Big_Big(&re,b.re,b.re);
	Mul_Big_Big(&m,b.im,b.im);
	Add_Big_Big(&m,m,m);
	CBigInt_substract(&re,re,m);

	Mul_Big_Big(&im,b.re,b.im);
	Add_Big_Big(&im,im,im);

    F2_construct(p,re,im);
}

/*
   二次扩域元素的逆运算
 (a+bu)^(-1)=(a-bu)/(a^2-b^2 u^2 )=(a-bu)/(a^2+2b^2 )

 */
void  F2_inverse( BNField2 *p, BNField2 b)
{
   
	CBigInt m,n;

	Mul_Big_Big(&m,b.re,b.re);
	Mul_Big_Big(&n,b.im,b.im);
	Add_Big_Big(&n,n,n);
	Add_Big_Big(&m,m,n);
	Inv(&m,m,BN.q);

	Mul_Big_Big(&p->re,b.re,m);
	Mul_Big_Big(&p->im,b.im,m);
	CBigInt_neg(&p->im,p->im);
	F2_construct(p,p->re,p->im); 

}

/*
  显示二次扩域元素
  按10进制或16进制格式输出到字符串
 */
void F2_toString(BNField2 b,unsigned int system)
{  
   printf("%s u + ",Put(b.im,system));
   printf("%s",Put(b.re,system));
}



/*
  规约化处理 
  */
 void F2_normorlize(BNField2 *b, BNField2 p)
{	 
     Mov_Big_Big(&b->re,p.re);
	 Mov_Big_Big(&b->im,p.im);
	 if(Cmp(b->re,BN.q)>0)
		 Mod_Big_Big(&b->re,b->re,BN.q);
	 if(Cmp(b->im,BN.q)>=0)
		 Mod_Big_Big(&b->im,b->im,BN.q);	 
}
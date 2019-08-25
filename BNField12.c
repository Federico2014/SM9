# include "BNField12.h"

/*
   初始化  
 */
void BNField12_init(BNField12 *b)
{  
	BNField4_init(&b->re);
	BNField4_init(&b->im);	
	BNField4_init(&b->sq);
}


/*
   十二次扩域的构造函数  

 */
 void F12_construct(BNField12 *b, BNField4 re, BNField4 im, BNField4 sq)
{	 
	F4_assign(&b->re,re);
	F4_assign(&b->im,im);
	F4_assign(&b->sq,sq);
}

/*
  规约化处理
 */
void F12_normorlize(BNField12 *p, BNField12 b)
{    
	F4_normorlize(&p->re,b.re);
	F4_normorlize(&p->im,b.im);
	F4_normorlize(&p->sq,b.sq);
}


/*
  赋值函数 p=b 
 */
void F12_assign(BNField12 *p,BNField12 b)
{     
	F4_assign(&p->re,b.re);
	F4_assign(&p->im,b.im);
	F4_assign(&p->sq,b.sq);
}

/*
  赋值函数p=1 
 */
void F12_assign_1(BNField12 *p)
{ 
	
	BNField2 t1;
	BNField4 t2;

	F2_construct(&t1,BN.ONE,BN.ZERO);
	F2_assign(&t2.re,t1);
 	F2_construct(&t1,BN.ZERO,BN.ZERO);
	F2_assign(&t2.im,t1);
	F4_assign(&p->re,t2);
	F4_construct(&t2,t1,t1);
	F4_assign(&p->im,t2);
	F4_assign(&p->sq,t2);
}


/*
   和十二次扩域元素相加  

 */
void  F12_add(BNField12 *b3, BNField12 b1, BNField12 b2)
{    
	F4_add(&b3->re,b1.re,b2.re);
	F4_add(&b3->im,b1.im,b2.im);
	F4_add(&b3->sq,b1.sq,b2.sq);
}

/*
   和四次次扩域元素相加  
 */
void  F12_add_F4(BNField12 *p, BNField12 b, BNField4 k)
{
    
	F4_add(&p->re,b.re,k);
	F4_assign(&p->im,b.im);
	F4_assign(&p->sq,b.sq);
}

/*
   十二次扩域元素相减  
 */
void  F12_substract(BNField12 *b3,BNField12 b1, BNField12 b2)
{	
	F4_substract(&b3->re,b1.re,b2.re);
    F4_substract(&b3->im,b1.im,b2.im);
	F4_substract(&b3->sq,b1.sq,b2.sq);
}


/*
   十二次扩域元素减去一个四次扩域元素  
*/
 void  F12_substract_F4(BNField12 *p, BNField12 b, BNField4 k)
 {     
	 F4_substract(&p->re,b.re,k);
	 F4_assign(&p->im,b.im);
	 F4_assign(&p->sq,b.sq);
 }


/*
   若12次扩域元素为0,则返回1，否则返加0；

 */
int F12_isZero(BNField12 b)
{
	return F4_isZero(b.re) && F4_isZero(b.im) && F4_isZero(b.sq);
}

/*
   若12次扩域元素为1,则返回1，否则返加0；

 */
int F12_isOne(BNField12 b)
{
	return F4_isOne(b.re) && F4_isZero(b.im)  && F4_isZero(b.sq);
}

/*
   若两个12次扩域元素相等,则返回1，否则返加0；

 */
int F12_equal(BNField12 b1, BNField12 b2)
{
	return F4_equal(b1.re,b2.re) && F4_equal(b1.im,b2.im)  && F4_equal(b1.sq,b2.sq);
}


/*
   12次扩域元素的负值；

 */
void F12_negate(BNField12 *p, BNField12 b)
{    
	F4_negate(&p->re,b.re);
	F4_negate(&p->im,b.im);
	F4_negate(&p->sq,b.sq);
}

/*
   十二次扩域元素的Frobenius值；

 */
void F12_frobenius(BNField12 *p, BNField12 b)
{
	F4_frobenius(&p->re,b.re);
	F4_frobenius(&p->im,b.im);
	F4_multiply_I(&p->im,p->im,BN.exp__2);
	F4_frobenius(&p->sq,b.sq);
	F4_multiply_I(&p->sq,p->sq,BN.exp_4);
}

/*
   十二次扩域元素的广义Frobenius值；

 */
void  F12_GFrobenius(BNField12 *p, BNField12 b, unsigned int e)
{	
	CBigInt d1,d2;
	switch (e)
	{
	  case 2: 
		  Get(&d1,"5958342662901643427453578939755302545063035311436308304692",DEC);  //(-2)^((q^2-1)/12) mod q
		  Get(&d2,"5958342662901643427453578939755302545063035311436308304691",DEC); 
		  break;
	  case 3:
		  Get(&d1,"49027451696706212072049108441259109200986788103413520360356476091992042164241",DEC); 
		  Get(&d2,"82434016654578246444830763105245969129603161266935169637912592173415460324732",DEC); 
		  break;
	  case 6:
		  Get(&d1,"82434016654578246444830763105245969129603161266935169637912592173415460324732",DEC);  //(-2)^((q^6-1)/12) mod q
		  Get(&d2,"1",DEC);       //(4)^((q^6-1)/12) mod q
	}

	F4_GFrobenius(&p->re,b.re,e);	
	F4_GFrobenius(&p->im,b.im,e);    
	F4_multiply_I(&p->im,p->im,d1);   
	F4_GFrobenius(&p->sq,b.sq,e);
	F4_multiply_I(&p->sq,p->sq,d2);	
}

/*
   (a+bw+cw^2)(a'+b'w+c'w^2)  ；
       =aa'+((b+c)(b'+c')-bb'-cc')v+((a+b)(a'+b')-aa'-bb'+cc'v)w
	           + ((a+c)(a'+c')-aa'-cc'+bb')w^2
 */
void  F12_multiply(BNField12 *b3, BNField12 b1, BNField12 b2)
{
    
	BNField4 t1,t2,t3,t4,re,im,sq;
	
    F4_multiply(&t1,b1.re,b2.re);  //
	F4_multiply(&t2,b1.im,b2.im);
	F4_multiply(&t3,b1.sq,b2.sq);
	F4_add(&t4,b1.im,b1.sq);	

	F4_add(&re,b2.im,b2.sq);
	F4_multiply(&re,re,t4);
	F4_substract(&re,re,t2);
	F4_substract(&re,re,t3);
	F4_multiply_v(&re,re);
	F4_add(&re,re,t1);

    F4_add(&t4,b1.re,b1.im);
	F4_add(&im,b2.re,b2.im);
	F4_multiply(&im,im,t4);
	F4_substract(&im,im,t1);
	F4_substract(&im,im,t2);
	F4_multiply_v(&t4,t3);
	F4_add(&im,im,t4);

    F4_add(&t4,b1.re,b1.sq);
	F4_add(&sq,b2.re,b2.sq);
	F4_multiply(&sq,sq,t4);
	F4_substract(&sq,sq,t1);
	F4_substract(&sq,sq,t3);
	F4_add(&sq,sq,t2);

	F4_assign(&b3->re,re);
	F4_assign(&b3->im,im);
	F4_assign(&b3->sq,sq);
}


/* 
   乘以四次扩域元素
   (a+bw+cw^2)k  ；
       =ka+kbw+kcw^2
 */
void F12_multiply_F4(BNField12 *p,BNField12 b, BNField4 k)
{	
    F4_multiply(&p->re,b.re,k);
	F4_multiply(&p->im,b.im,k);
	F4_multiply(&p->sq,b.sq,k);

}

/*
   乘以小数 
   (a+bw+cw^2)k  ；
       =ka+kbw+kcw^2
 */
void F12_multiply_i(BNField12 *p, BNField12 b, int k)
{	 
	F4_multiply_i(&p->re,b.re,k);
	F4_multiply_i(&p->im,b.im,k);
	F4_multiply_i(&p->sq,b.sq,k);
}

/*
   乘以大数 
   (a+bw+cw^2)k  ；
       =ka+kbw+kcw^2
 */
void  F12_multiply_I(BNField12 *p, BNField12 b, CBigInt k)
{
	
	F4_multiply_I(&p->re,b.re,k);
	F4_multiply_I(&p->im,b.im,k);
	F4_multiply_I(&p->sq,b.sq,k);
}



/*
   十二次扩域元素的平方运算
   (a+bw+cw^2)^2  ；
       =a^2+((b+c)^2-b^2-c^2)v+((a+b)^2-a^2-b^2+c^2 v)w
	           + ((a+c)^2-a^2-c^2+b^2)w^2

 */
void  F12_square(BNField12 *p, BNField12 b)
{
	
	BNField4 t1,t2,t3,t4,re,im,sq;

    F4_square(&t1,b.re);
	F4_square(&t2,b.im);
	F4_square(&t3,b.sq);

	F4_add(&re,b.im,b.sq);
	F4_square(&re,re);
	F4_substract(&re,re,t2);
	F4_substract(&re,re,t3);
	F4_multiply_v(&re,re);
	F4_add(&re,re,t1);

	F4_add(&im,b.re,b.im);
	F4_square(&im,im);
	F4_substract(&im,im,t1);
	F4_substract(&im,im,t2);
	F4_multiply_v(&t4,t3);
	F4_add(&im,im,t4);

	F4_add(&sq,b.re,b.sq);
	F4_square(&sq,sq);
	F4_substract(&sq,sq,t1);
	F4_substract(&sq,sq,t3);
	F4_add(&sq,sq,t2);

	F4_assign(&p->re,re);
	F4_assign(&p->im,im);
	F4_assign(&p->sq,sq);
}


/*
   十二次扩域元素的逆运算
 (a+bw+cw^2)^(-1)=(A+Bw+Cw^2)/(bCv+aA+cBv)
 其中 A = a^2-bcv
      B = c^2 v-ab
	  C = b^2-ac
 */
void  F12_inverse(BNField12 *p, BNField12 b)
{    
	BNField4 t1,t2,t3;
	BNField4 A,B,C;
    
    F4_square(&t1,b.re);
	F4_square(&t2,b.im);
	F4_square(&t3,b.sq);

    F4_multiply(&A,b.im,b.sq);
    F4_multiply_v(&A,A);
    F4_substract(&A,t1,A);

	F4_multiply(&B,b.re,b.im);
	F4_multiply_v(&t3,t3);
	F4_substract(&B,t3,B);

	F4_multiply(&C,b.re,b.sq);
    F4_substract(&C,t2,C);
  
	F4_multiply(&t1,b.im,C);
    F4_multiply_v(&t1,t1);
	F4_multiply(&t2,b.re,A);
    F4_add(&t1,t1,t2);
    F4_multiply(&t2,b.sq,B);
	F4_multiply_v(&t2,t2);
    F4_add(&t1,t1,t2);

	F4_inverse(&t1,t1);
	F4_multiply(&p->re,A,t1);
	F4_multiply(&p->im,B,t1);
	F4_multiply(&p->sq,C,t1);

}

/*
  计算 *p = b^e，e为大于或等于0的正整数
 
*/

void F12_exp(BNField12 *p, BNField12 b, CBigInt e)
{
	char *bits,str[1024];
	int len,i;
	BNField12 q;
	if(F12_isZero(b))
		F12_assign(p,b);
	else
	{
		if(Cmp(e,BN.ZERO)==0)	
			F12_assign_1(p);		
        else 
		{

	    	bits = Put(e, 2);
	        len = strlen(bits);
			strcpy(str,bits);
        	F12_assign(&q,b);
           for(i=1;i<len;i++)
		   {
	    	   F12_square(&q,q);
	           if(str[i]=='1')
		           F12_multiply(&q,q,b);			   
		   }
		   F12_assign(p,q);
		}    	
	}
}


/*
  显示十二次扩域元素
 */
void F12_toString_d(BNField12 b,unsigned int system)
{
//   gmp_printf("(%Zd u, %Zd)\n",b.im,b.re);
   printf("{");
   F4_toString(b.sq,system);
   printf(" w^2 + ");
   F4_toString(b.im,system);
   printf(" w + ");
   F4_toString(b.re,system);
   printf("} \n");
}


/*
  十六进或十进制显示十二次扩域元素
*/
void F12_toString(BNField12 b,unsigned int system)
{

  char *str;
   str = Put(b.sq.im.im,system); printf("(%s,\n",str);
   str = Put(b.sq.im.re,system); printf(" %s,\n",str);
   str = Put(b.sq.re.im,system); printf(" %s,\n",str);
   str = Put(b.sq.re.re,system); printf(" %s,\n",str);
   str = Put(b.im.im.im,system); printf(" %s,\n",str);
   str = Put(b.im.im.re,system); printf(" %s,\n",str);
   str = Put(b.im.re.im,system); printf(" %s,\n",str);
   str = Put(b.im.re.re,system); printf(" %s,\n",str);
   str = Put(b.re.im.im,system); printf(" %s,\n",str);
   str = Put(b.re.im.re,system); printf(" %s,\n",str);
   str = Put(b.re.re.im,system); printf(" %s,\n",str);
   str = Put(b.re.re.re,system); printf(" %s)\n",str);

  }

 
#include "BNPoint2.h"
 
/*
    BNPoint2 初始化  

 */
void BNPoint2_init(BNPoint2 *p)
{
    BNField2_init(&p->x);
	BNField2_init(&p->y);
	BNField2_init(&p->z);
    
	F2_construct(&p->x,BN.ZERO,BN.ZERO);
	F2_construct(&p->y,BN.ZERO,BN.ZERO);
	F2_construct(&p->z,BN.ONE,BN.ZERO);
}


/*
    BNPoint2 构造函数  
*/
 void P2_construct(BNPoint2 *p, BNField2 x, BNField2 y, BNField2 z)
 {     
	 F2_assign(&p->x,x);
	 F2_assign(&p->y,y);
	 F2_assign(&p->z,z);
 }

/*
    BNPoint2 构造函数  
*/
 void P2_construct_xy(BNPoint2 *p, BNField2 x, BNField2 y)
 {
     
	 F2_assign(&p->x,x);
	 F2_assign(&p->y,y);
	 F2_construct(&p->z,BN.ONE,BN.ZERO);
 }

 /*
   赋值函数 *p = b
 */
void P2_assign(BNPoint2 *p, BNPoint2 b)
{	 
	F2_assign(&p->x,b.x);
	F2_assign(&p->y,b.y);
	F2_assign(&p->z,b.z);
}

/*
   若BNPoint2为0,则返回1，否则返加0；
 */
int P2_isZero(BNPoint2 p)
{
	return F2_isZero(p.z);
}


/*
  Jacobian坐标系下的规约处理
  x = X/Z^2, y = Y/Z^3
 */
void P2_normorlize(BNPoint2 *p, BNPoint2 b)
{
	
	BNField2 m,n;

	if(!(P2_isZero(b)))
	{
		F2_multiply(&m,b.z,b.z);
		F2_multiply(&n,m,b.z);
        F2_inverse(&m,m);
		F2_inverse(&n,n);
		F2_multiply(&p->x,b.x,m);
		F2_multiply(&p->y,b.y,n);
		F2_construct(&p->z,BN.ONE,BN.ZERO);
	}else
		P2_assign(p,b);
}

/*
   判断BNPoint是否为规范类型，若是返加1，否则返回0；

 */
int P2_isNormal(BNPoint2 p)
{
	return F2_isZero(p.z) || F2_isOne(p.z);
}


/*
   若两个域元素相等,则返回1，否则返加0；

 */
int P2_equal(BNPoint2 p1, BNPoint2 p2)
{
	//BNPoint2 p3,p4;
	if(P2_isZero(p1))
	{
		if(P2_isZero(p2))
			return 1;
		else
			return 0;
	}
	else if(P2_isZero(p2))
		return 0;
	else
	{
		if(!P2_isNormal(p1))
	    	 P2_normorlize(&p1,p1);
		if(!P2_isNormal(p2))			
	    	 P2_normorlize(&p2,p2);

		if(F2_equal(p1.x,p2.x) && F2_equal(p1.y,p2.y))
			return 1;
		else 
			return 0;
	}

}

/*
   BNPoint2的负值；

 */
void  P2_negate(BNPoint2 *p, BNPoint2 b)
{
	
	F2_assign(&p->x,b.x);
	F2_negate(&p->y,b.y);
	F2_assign(&p->z,b.z);
}

/*
   BNPoint2: *p = p1 + p2；

 */

void P2_add(BNPoint2 *p, BNPoint2 p1, BNPoint2 p2)
{
	
	BNField2 t1,t2,t3,t4,t5;
	BNField2 A,B,C,D,x,y,z;

	if(P2_isZero(p1))
		P2_assign(p,p2);
	else if(P2_isZero(p2))
		P2_assign(p,p1);
	else if(P2_equal(p1,p2))
		P2_twice(p,p1);
	else
	{       
       F2_square(&t1,p1.z);
	   F2_square(&t2,p2.z);
	   F2_multiply(&t3,t1,p1.z);
	   F2_multiply(&t4,t2,p2.z);
	   F2_multiply(&t3,p2.y,t3);
	   F2_multiply(&A,p1.y,t4);
	   F2_substract(&A,t3,A);

	   
	   F2_multiply(&t3,p2.x,t1);
       F2_multiply(&t5,p1.x,t2);
	   F2_substract(&B,t3,t5);


	   F2_multiply(&C,p1.z,p2.z);
       F2_add(&D,t3,t5);


       F2_square(&t3,B);
	   F2_multiply(&t5,t3,D);
	   F2_square(&x,A);
	   F2_substract(&x,x,t5);

       F2_multiply(&t5,t3,t2);
	   F2_multiply(&t5,p1.x,t5);
	   F2_substract(&t5,t5,x);
	   F2_multiply(&t5,A,t5);
	   F2_multiply(&t3,t3,B);
	   F2_multiply(&t3,t3,t4);
       F2_multiply(&t3,p1.y,t3);
	   F2_substract(&y,t5,t3);

	   F2_multiply(&z,B,C);
	   P2_construct(p,x,y,z);
	}
}


/*
   BNPoint: *p = 2*q；

 */

void P2_twice(BNPoint2 *p, BNPoint2 q)
{
     
	BNField2 t1,t2,t3,t4,t5;
	BNField2 x,y,z;
	
	if(P2_isZero(q))
		P2_assign(p,q);
	else
	{
		F2_multiply(&t1,q.x,q.x);
		F2_multiply(&t2,t1,t1);
		F2_multiply_i(&t2,t2,9);
        F2_multiply(&t3,q.y,q.y);
		F2_multiply(&t4,t3,q.x);
		F2_multiply_i(&t5,t4,8);
        
		 F2_substract(&x,t2,t5);
		F2_multiply_i(&t5,t4,4);
		F2_substract(&t5,t5,x);
		F2_multiply(&t5,t5,t1);
		F2_multiply_i(&t5,t5,3);
		F2_square(&t4,t3);       //有改动
		F2_multiply_i(&t4,t4,8);
		F2_substract(&y,t5,t4);
		F2_multiply(&z,q.y,q.z);
		F2_add(&z,z,z);

		P2_construct(p,x,y,z);
	}
}

/*
  计算 BNPoint: *p = k*q；

 */

void P2_multiply(BNPoint2 *p, BNPoint2 q, CBigInt k)
{
	
	char *bits,str[1024];
	int len;
	int i;
	BNPoint2 t; 
	if(Cmp(k,BN.ZERO)==0)
		F2_construct(&t.z,BN.ZERO,BN.ZERO);
    else 
	{		
		bits = Put(k,2);
	    len = strlen(bits);
		strcpy(str,bits);
    	P2_assign(&t,q);
     for(i=1;i<len;i++)
	   {
	    	P2_twice(&t,t);
	    	if(str[i]=='1')	
		    	P2_add(&t,t,q);
	   }
	}
  	P2_assign(p,t);
}

/*
判断点是否在BN扭曲线y^2 = x^3 + 5u z^6

*/

int P2_isOnBNTCurve(BNPoint2 p)
{
	BNField2 a,b,c,d;

	F2_multiply(&a,p.y,p.y);
	F2_multiply(&b,p.x,p.x);
	F2_multiply(&b,b,p.x);
    F2_multiply(&c,p.z,p.z);
    F2_multiply(&d,c,c);
	F2_multiply(&d,d,c);
	F2_multiply_u(&d,d);
	F2_multiply_i(&d,d,5);
	F2_add(&d,d,b);

	return F2_equal(a,d) ? 1 : 0;
}


/*
 BNPoint2: Frobeniuse 计算
 */
void P2_frobenius(BNPoint2 *p, BNPoint2 q)
{
	
	CBigInt a,b;

	Inv(&a,BN.exp_4,BN.q);
	Inv(&b,BN.exp__8,BN.q);

	if(!P2_isNormal(q))
		P2_normorlize(&q,q);
	F2_frobenius(&p->x,q.x);
	F2_multiply_I(&p->x,p->x,a);
	F2_frobenius(&p->y,q.y);
	F2_multiply_I(&p->y,p->y,b);
	F2_construct(&p->z,BN.ONE,BN.ZERO);
}


/*
   打印显示BNPoint；
 */

void P2_toString_d(BNPoint2 p,unsigned int system)
{
	if(P2_isZero(p))
		printf("0\n");
	else
  	{
		printf("[");
		F2_toString(p.x,system);
		printf(",");
	    F2_toString(p.y,system);
		printf(",");
	    F2_toString(p.z,system);
		printf("]\n");
	}
}

/*
   十六进制或十进制打印显示BNPoint2；
 */

void P2_toString(BNPoint2 p,unsigned int system)
{
	char *str;
	if(P2_isZero(p))
		printf("0\n");
	else
  	{
		str = Put(p.x.im,system); printf("[(%s,\n",str);
		str = Put(p.x.re,system); printf("%s),\n",str);
		str = Put(p.y.im,system); printf("(%s,\n",str);
		str = Put(p.y.re,system); printf("%s),\n",str);
		str = Put(p.z.im,system); printf("(%s,\n",str);
		str = Put(p.z.re,system); printf("%s)]\n",str);		
	}
}
#include "sm9/curve/point.h"

/*
    BNPoint initialization
 */
void BNPoint_init(BNPoint *p)
{
	CBigIntInit(&p->x);
	CBigIntInit(&p->y);
	CBigIntInit(&p->z);
}


/*
    BNPoint constructor
*/
void P_construct(BNPoint *p, CBigInt x, CBigInt y, CBigInt z)
{
	Mov_Big_Big(&p->x,x);
	Mov_Big_Big(&p->y,y);
	Mov_Big_Big(&p->z,z);

	if(Cmp(p->x,BN.q)>=0)
		Mod_Big_Big(&p->x,p->x,BN.q);

	if(Cmp(p->y,BN.q)>=0)
		Mod_Big_Big(&p->y,p->y,BN.q);

	if(Cmp(p->z,BN.q)>=0)
		Mod_Big_Big(&p->z,p->z,BN.q);
}

/*
    BNPoint constructor
*/
void P_construct_xy(BNPoint *p, CBigInt x, CBigInt y)
{
	Mov_Big_Big(&p->x,x);
	Mov_Big_Big(&p->y,y);
	Mov_Big_Long(&p->z,1);

	if(Cmp(p->x,BN.q)>=0)
		Mod_Big_Big(&p->x,p->x,BN.q);

	if(Cmp(p->y,BN.q)>=0)
		Mod_Big_Big(&p->y,p->y,BN.q);

}

/*
   Assignment: *p = b
 */
void P_assign(BNPoint *p, BNPoint b)
{
	Mov_Big_Big(&p->x,b.x);
	Mov_Big_Big(&p->y,b.y);
	Mov_Big_Big(&p->z,b.z);
}

/*
   Check if BNPoint is zero, return 1 if zero, otherwise return 0
 */
int P_isZero(BNPoint p)
{
	return Cmp(p.z,BN.ZERO)==0 ;
}


/*
  Normalization in Jacobian coordinates
  x = X/Z^2, y = Y/Z^3
 */
void P_normorlize(BNPoint *p,BNPoint b)
{
	CBigInt m,n;

	if(!(P_isZero(b)))
	{
		Mul_Big_Big(&m,b.z,b.z);
		Mul_Big_Big(&n,m,b.z);
		Inv(&m,m,BN.q);
		Inv(&n,n,BN.q);
		Mul_Big_Big(&p->x,b.x,m);
		Mul_Big_Big(&p->y,b.y,n);

		if(Cmp(p->x,BN.q)>=0)
			Mod_Big_Big(&p->x,p->x,BN.q);

		if(Cmp(p->y,BN.q)>=0)
			Mod_Big_Big(&p->y,p->y,BN.q);
		Mov_Big_Long(&p->z,1);
	}
	else
		P_assign(p,b);
}

/*
   Check if BNPoint is normalized, return 1 if z=0 or z=1, otherwise return 0
 */
int P_isNormal(BNPoint p)
{
	return Cmp(p.z,BN.ZERO)==0 || Cmp(p.z,BN.ONE)==0;
}


/*
   Compare two elements, return 1 if equal, otherwise return 0
 */
int P_equal(BNPoint p1, BNPoint p2)
{
	if(P_isZero(p1))
	{
		if(P_isZero(p2))
			return 1;
		else
			return 0;
	}
	else if(P_isZero(p2))
		return 0;
	else
	{
		if(!P_isNormal(p1))
		{
	    	P_normorlize(&p1,p1);
		}
		if(!P_isNormal(p2))
		{
	    	P_normorlize(&p2,p2);
		}

		if(Cmp(p1.x,p2.x) == 0 && Cmp(p1.y,p2.y) == 0)
			return 1;
		else
			return 0;
	}

}

/*
   BNPoint negation
   P = (x,y,z)
   -P = (x,-y,z)
 */
void P_negate(BNPoint *p, BNPoint b)
{
	Mov_Big_Big(&p->x,b.x);
	CBigInt_neg(&p->y,b.y);
	Mov_Big_Big(&p->z,b.z);
}

/*
   BNPoint addition: *p = p1 + p2
 */
void P_add(BNPoint *p, BNPoint p1, BNPoint p2)
{
	CBigInt t1,t2,t3,t4,t5;
	CBigInt A,B,C,D,x,y,z;

	if(P_isZero(p1))
		P_assign(p,p2);
	else if(P_isZero(p2))
		P_assign(p,p1);
	else if(P_equal(p1,p2))
		P_twice(p,p1);
	else
	{
	   Mul_Big_Big(&t1,p1.z,p1.z);
	   Mul_Big_Big(&t2,p2.z,p2.z);
	   Mul_Big_Big(&t3,t1,p1.z);
	   Mod_Big_Big(&t3,t3,BN.q); //mod reduction to prevent overflow
	   Mul_Big_Big(&t4,t2,p2.z);
	   Mod_Big_Big(&t4,t4,BN.q); //mod reduction to prevent overflow
	   Mul_Big_Big(&t3,p2.y,t3);
	   Mul_Big_Big(&A,p1.y,t4);
	   CBigInt_substract(&A,t3,A);

	   Mul_Big_Big(&t3,p2.x,t1);
	   Mul_Big_Big(&t5,p1.x,t2);
	   CBigInt_substract(&B,t3,t5);

	   Mul_Big_Big(&C,p1.z,p2.z);
	   Add_Big_Big(&D,t3,t5);
	   Mod_Big_Big(&D,D,BN.q); //mod reduction to prevent overflow

	   Mul_Big_Big(&t3,B,B);
	   Mul_Big_Big(&t5,t3,D);
	   Mul_Big_Big(&x,A,A);
	   CBigInt_substract(&x,x,t5);

	   Mod_Big_Big(&t2,t2,BN.q);  //mod reduction to prevent overflow
	   Mod_Big_Big(&t3,t3,BN.q);  //mod reduction to prevent overflow
	   Mul_Big_Big(&t5,t3,t2);
	   Mul_Big_Big(&t5,p1.x,t5);
	   CBigInt_substract(&t5,t5,x);
	   Mul_Big_Big(&t5,A,t5);
	   Mul_Big_Big(&t3,t3,B);
	   Mul_Big_Big(&t3,t3,t4);
	   Mod_Big_Big(&t3,t3,BN.q);  //mod reduction to prevent overflow
	   Mul_Big_Big(&t3,p1.y,t3);
	   CBigInt_substract(&y,t5,t3);

	   Mul_Big_Big(&z,B,C);

	   P_construct(p,x,y,z);
	}
}


/*
   BNPoint doubling: *p = 2*q
 */
void P_twice(BNPoint *p, BNPoint q)
{
	CBigInt t1,t2,t3,t4,t5;
	CBigInt x,y,z;

	if(P_isZero(q))
		P_assign(p,q);
	else
	{
		Mul_Big_Big(&t1,q.x,q.x);
		Mod_Big_Big(&t1,t1,BN.q);   //mod reduction to prevent overflow
		Mul_Big_Big(&t2,t1,t1);
		Mod_Big_Big(&t2,t2,BN.q);   //mod reduction to prevent overflow
		Mul_Big_Long(&t2,t2,9);
		Mul_Big_Big(&t3,q.y,q.y);
		Mul_Big_Big(&t4,t3,q.x);
		Mod_Big_Big(&t4,t4,BN.q);   //mod reduction to prevent overflow
		Mul_Big_Long(&t5,t4,8);

		CBigInt_substract(&x,t2,t5);
		Mul_Big_Long(&t5,t4,4);
		CBigInt_substract(&t5,t5,x);
		Mod_Big_Big(&t1,t1,BN.q);   //mod reduction to prevent overflow
		Mul_Big_Big(&t5,t5,t1);
		Mul_Big_Long(&t5,t5,3);
		Mod_Big_Big(&t5,t5,BN.q);  //mod reduction to prevent overflow
		Mod_Big_Big(&t3,t3,BN.q);  //mod reduction to prevent overflow
		Mul_Big_Big(&t4,t3,t3);
		Mul_Big_Long(&t4,t4,8);
		CBigInt_substract(&y,t5,t4);
		Mul_Big_Big(&z,q.y,q.z);
		Add_Big_Big(&z,z,z);

		P_construct(p,x,y,z);
	}
}

/*
  Scalar multiplication BNPoint: *p = k*q
  k must be an integer greater than or equal to 0
 */
void P_multiply(BNPoint *p, BNPoint q, CBigInt k)
{
	char *bits,str[1024];
	int len,i;
	BNPoint t;
	if(Cmp(k,BN.ZERO)==0)
		Mov_Big_Long(&t.z,0);
	else
	{
		bits = Put(k,2);
		len = strlen(bits);

		//str = (char *)malloc(len);
	//	for(i=0; i<len; i++)
	//		str[i] = bits[i];
		strcpy(str,bits);
		P_assign(&t,q);

		for(i=1;i<len;i++)
		{
			P_twice(&t,t);
			if(str[i]=='1')
				P_add(&t,t,q);
		}
	}
	P_assign(p,t);
}

/*
Check if point is on BN curve y^2 = x^3 + 5 z^6
*/
int P_isOnBNCurve(BNPoint p)
{
	CBigInt a,b,c,d;
	Mul_Big_Big(&a,p.y,p.y);
	Mul_Big_Big(&b,p.x,p.x);
	Mul_Big_Big(&b,b,p.x);
	Mul_Big_Big(&c,p.z,p.z);
	Mul_Big_Big(&c,c,p.z);
	Mod_Big_Big(&c,c,BN.q); //mod reduction to prevent overflow
	Mul_Big_Big(&d,c,c);
	Mul_Big_Long(&d,d,5);
	Add_Big_Big(&d,d,b);
	Mod_Big_Big(&a,a,BN.q);
	Mod_Big_Big(&d,d,BN.q);

	return Cmp(a,d) == 0 ? 1 : 0;

}


/*
   Print BNPoint
 */
void P_toString(BNPoint p,unsigned int system)
{
	char *str;
	if(P_isZero(p))
		printf("0\n");
	else
	{
		str = Put(p.x,system);  printf("[%s,",str);
		str = Put(p.y,system);  printf("%s,",str);
		str = Put(p.z,system);  printf("%s]\n",str);
	}
}


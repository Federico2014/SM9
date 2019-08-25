# include "BNPairing.h"


/*
    线函数的计算 
*/
void Line_Funtion(BNField12 *f, BNPoint2 T, BNPoint2 Q, BNPoint P)
{
	
	BNField2 t1,t2,t3,t4,t5;
	
    if(P2_equal(T,Q))
	{
		F2_square(&t1,T.z);
		F2_multiply(&t2,t1,T.z);	  
		F2_multiply_I(&t2,t2,P.y);
	
		F2_negate(&t4,T.y);
		F4_construct(&f->re,t4,t2);	
		F4_multiply_F2(&f->re,f->re,T.y);

		F4_add(&f->re,f->re,f->re);


		F2_square(&t2,T.x);
		F2_multiply(&t3,t2,T.x);
		F2_multiply_i(&t3,t3,3);
			
		F4_add_F2(&f->re,f->re,t3);

        F2_multiply(&t2,t2,t1);
		F2_multiply_I(&t2,t2,P.x);
		F2_multiply_i(&t2,t2,3);
		F2_negate(&t2,t2);
		F4_construct_F2(&f->sq,t2);
	}
	else
	{
		F2_square(&t1,Q.z);
	    F2_multiply(&t2,t1,Q.z);
    	F2_multiply_I(&t3,t2,P.y);
    	F2_negate(&t4,Q.y);
		F4_construct(&f->re,t4,t3);
		F4_multiply_F2(&f->re,f->re,T.z);
    
        F2_square(&t5,T.z);
    	F2_multiply(&t3,t5,Q.x);
    	F2_multiply(&t4,T.x,t1);
	    F2_substract(&t3,t3,t4);
		F4_multiply_F2(&f->re,f->re,t3);

    	F2_multiply(&t5,t5,T.z);
    	F2_multiply(&t3,Q.y,t5);
	    F2_multiply(&t4,T.y,t2);
        F2_substract(&t3,t3,t4);
        F2_multiply(&t5,t3,Q.x);
		F4_add_F2(&f->re,f->re,t5);

        F2_multiply(&t3,t3,t1);
        F2_multiply_I(&t3,t3,P.x);
        F2_negate(&t3,t3);
		F4_construct_F2(&f->sq,t3);
	}

	    F2_construct(&t5,BN.ZERO,BN.ZERO);
		F4_construct(&f->im,t5,t5);
}

/*
    最终幂的计算 f = b^((b^12-1)/12)
*/
void Final_exp(BNField12 *f, BNField12 p)
{
	
	BNField12 f1,f2;
	BNField12 ff1,ff2,ff3;
	BNField12 a, b;
	CBigInt k1,k2;

	Mov_Big_Long(&k1,9);
	Mov_Big_Long(&k2,4);
	
    F12_GFrobenius(&f1,p,6);   // e = 6
	F12_inverse(&f2,p);
	F12_multiply(&f1,f1,f2);	
    F12_GFrobenius(&f2,f1,2);    // e = 2		 
	F12_multiply(&f1,f1,f2);			

	F12_exp(&a,f1,BN.exp_6t_5);      // exp1
    F12_inverse(&a,a);
	F12_frobenius(&b,a);
	F12_multiply(&b,b,a);

	F12_frobenius(&ff1,f1);
	F12_square(&ff2,ff1);
	F12_multiply(&ff2,b,ff2);
	F12_GFrobenius(&ff3,f1,2);     // e = 2
	F12_multiply(&ff2,ff2,ff3);
	F12_exp(&ff2,ff2,BN.exp_6t_2_1);	   
	
	F12_GFrobenius(&ff3,f1,3);       // e = 3
	F12_multiply(&ff2,ff2,ff3);
  	F12_multiply(&ff2,ff2,a);  
  	F12_multiply(&ff2,ff2,b); 

  	F12_multiply(&ff3,f1,ff1); 
    F12_exp(&ff3,ff3,k1);
  	F12_multiply(&ff2,ff2,ff3); 

    F12_exp(&ff3,f1,k2);
  	F12_multiply(&ff2,ff2,ff3); 

	F12_assign(f,ff2);

}

/*
  最优对的计算
  注意：P需为规范化形式
 */
void Pairing_opt(BNField12 *f,BNPoint2 Q, BNPoint P)
{   
	BNField12 ff;
	BNPoint2 T,Q1,Q2;
	char *str,bits[1024];
	int len,i;

	F12_assign_1(f); 
	if(!P_isZero(P) && !P2_isZero(Q))
	{

       P2_assign(&T,Q);
	   str = Put(BN.ord,2);
	   len = strlen(str);
	   strcpy(bits,str);

     for(i=1; i<len; i++)
	 {
		F12_square(f,*f);
	    Line_Funtion(&ff,T,T,P);				

		F12_multiply(f,*f,ff);
		P2_twice(&T,T);
	    if(bits[i]=='1')
		{
	    	Line_Funtion(&ff,T,Q,P);
			F12_multiply(f,*f,ff);
			P2_add(&T,T,Q);
		}
	 }	

	P2_frobenius(&Q1,Q);	
	P2_frobenius(&Q2,Q1);
	P2_negate(&Q2,Q2);
	Line_Funtion(&ff,T,Q1,P);
	F12_multiply(f,*f,ff);
	P2_add(&T,T,Q1);
	Line_Funtion(&ff,T,Q2,P);
	F12_multiply(f,*f,ff);		

    Final_exp(f,*f);

   }
}


/*
  Rate 对的计算

 */
void Pairing_Rate(BNField12 *f, BNPoint2 Q, BNPoint P)
{
	BNField12 ff;
	BNPoint2 T,T2,T3;
	char *str,bits[1024];
	int len,i;

	F12_assign_1(f); 
	if(!P_isZero(P)&& !P2_isZero(Q))
	{

      P2_assign(&T,Q);
	  str = Put(BN.ord,2);
	  len = strlen(str);
	  strcpy(bits,str);
//	F12_toString_d(*f);

    for(i=1; i<len; i++)
	{
		F12_square(f,*f);
		Line_Funtion(&ff,T,T,P);
		F12_multiply(f,*f,ff);
		P2_twice(&T,T);
	    if(bits[i]=='1')
		{
	    	Line_Funtion(&ff,T,Q,P);
			F12_multiply(f,*f,ff);
			P2_add(&T,T,Q);
		}
	}

	Line_Funtion(&ff,T,Q,P);    
    F12_multiply(&ff,*f,ff);
    F12_frobenius(&ff,ff);
	F12_multiply(f,*f,ff);

	P2_add(&T2,T,Q);
    P2_frobenius(&T3,T2);
	Line_Funtion(&ff,T3,T,P);   
	F12_multiply(f,*f,ff);

    Final_exp(f,*f);
	}
}
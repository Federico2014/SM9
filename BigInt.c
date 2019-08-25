
#include "BigInt.h"

//构造大数对象并初始化为零
void CBigIntInit(CBigInt *A)
{
	int i;
	A->m_nLength=1;
	for(i=0;i<BI_MAXLEN;i++)
		A->m_ulValue[i]=0;
}

/****************************************************************************************
大数比较
调用方式：Cmp(N,A)
返回值：若N<A返回-1；若N=A返回0；若N>A返回1
****************************************************************************************/
int Cmp(CBigInt N,CBigInt A)
{
	int i;
	if(N.m_nLength>A.m_nLength)
		return 1;
	if(N.m_nLength<A.m_nLength)
		return -1;
	for(i=N.m_nLength-1;i>=0;i--)
	{
		if(N.m_ulValue[i]>A.m_ulValue[i])
			return 1;
		if(N.m_ulValue[i]<A.m_ulValue[i])
			return -1;
	}
	return 0;
}

/****************************************************************************************
大数赋值
调用方式：Mov_Big_Big(N,A)
返回值：N,被赋值为A
****************************************************************************************/
void Mov_Big_Big(CBigInt *N, CBigInt A)
{
	//CBigInt N;
	int i;
	N->m_nLength=A.m_nLength;
	for(i=0;i<BI_MAXLEN;i++)
	{
		N->m_ulValue[i]=A.m_ulValue[i];
	}
	
}

void Mov_Big_Long(CBigInt * N, unsigned long A)
{	
	int i;
	if(A>0xffffffff)
	{
		N->m_nLength=2;
		N->m_ulValue[1]=(unsigned long)((unsigned long long)A>>32);
		N->m_ulValue[0]=(unsigned long)A;
	}
	else
	{
		N->m_nLength=1;
		N->m_ulValue[0]=(unsigned long)A;
	}
	for(i=N->m_nLength;i<BI_MAXLEN;i++)
	{
		N->m_ulValue[i]=0;
	}

}




/****************************************************************************************
大数相加
调用形式：Add_Big_Big(Y,N,A)
返回值：Y=N+A
****************************************************************************************/
void Add_Big_Big(CBigInt *Y, CBigInt N, CBigInt A)
{
	unsigned int i;
	CBigInt X;
	unsigned int carry=0;
	unsigned long long sum=0;
	CBigIntInit(&X);
	Mov_Big_Big(&X, N);

	if(X.m_nLength<A.m_nLength)
	{
		X.m_nLength=A.m_nLength;
	}
	for(i=0;i<X.m_nLength;i++)
	{
		sum=A.m_ulValue[i];
		sum=sum+X.m_ulValue[i]+carry;
		X.m_ulValue[i]=(unsigned long)sum;
		carry=(unsigned int)(sum>>32);
	}
	X.m_ulValue[X.m_nLength]=carry;
	X.m_nLength+=carry;	
	Mov_Big_Big(Y,X);
}

void Add_Big_Long(CBigInt *Y, CBigInt N, unsigned long A)
{
	CBigInt X;
	unsigned long long sum;
	CBigIntInit(&X);
	Mov_Big_Big(&X,N);

	sum=X.m_ulValue[0];
	sum+=A;     
	X.m_ulValue[0]=(unsigned long)sum;
	if(sum>0xffffffff)
	{
		unsigned int i=1;
		while(X.m_ulValue[i]==0xffffffff)
		{
			X.m_ulValue[i]=0;
			i++;
		}
		X.m_ulValue[i]++;
		if(N.m_nLength==i)
			N.m_nLength++;
	}
	Mov_Big_Big(Y,X);
}

/****************************************************************************************
大数相减
调用形式：Sub_Big_Big(Y,N,A)
返回值：Y=N-A
****************************************************************************************/
/*
void Sub_Big_Big(CBigInt *Y,CBigInt N, CBigInt A)
{
	CBigInt X;
	unsigned int carry=0;
	unsigned long long num;
	unsigned int i;
	CBigIntInit(&X);
	Mov_Big_Big(&X,N);
	if(Cmp(X,A)<=0)
	{
		Mov_Big_Long(&X,0);
		Mov_Big_Big(Y,X);
	}else
	{

		for(i=0;i<N.m_nLength;i++)
		{
			if((N.m_ulValue[i]>A.m_ulValue[i])||((N.m_ulValue[i]==A.m_ulValue[i])&&(carry==0)))
			{
				X.m_ulValue[i]=N.m_ulValue[i]-carry-A.m_ulValue[i];
				carry=0;
			}
			else
			{
				num=0x100000000+X.m_ulValue[i];
				X.m_ulValue[i]=(unsigned long)(num-carry-A.m_ulValue[i]);
				carry=1;
			}     
		}
		while(X.m_ulValue[X.m_nLength-1]==0)
			X.m_nLength--;
		Mov_Big_Big(Y,X);
	}
}
*/
void Sub_Big_Big(CBigInt *Y, CBigInt N, CBigInt A)
{
	CBigInt X;
	unsigned int carry=0;
	unsigned long long num;
	unsigned int i;
	CBigIntInit(&X);
	Mov_Big_Big(&X,N);
	if(Cmp(X,A)<=0)
		Mov_Big_Long(&X,0);
    else
	{

		for(i=0;i<N.m_nLength;i++)
		{
			if((N.m_ulValue[i]>A.m_ulValue[i])||((N.m_ulValue[i]==A.m_ulValue[i])&&(carry==0)))
			{
				X.m_ulValue[i]=N.m_ulValue[i]-carry-A.m_ulValue[i];
				carry=0;
			}
			else
			{
				num=0x100000000+X.m_ulValue[i];
				X.m_ulValue[i]=(unsigned long)(num-carry-A.m_ulValue[i]);
				carry=1;
			}     
		}
		while(X.m_ulValue[X.m_nLength-1]==0)
			X.m_nLength--;
			
	}
	Mov_Big_Big(Y,X);
}

void Sub_Big_Long(CBigInt *Y, CBigInt N, unsigned long A)
{
	CBigInt X;

	unsigned long long num;
	int i=1;
	CBigIntInit(&X);

	num=0x100000000+X.m_ulValue[0];

	Mov_Big_Big(&X,N);
	if(X.m_ulValue[0]>=A)
	{
		X.m_ulValue[0]-=A;
		Mov_Big_Big(Y,X);
	}
	else if(X.m_nLength==1)
	{
		Mov_Big_Long(&X,0);
		Mov_Big_Big(Y,X);
	}
	else
	{

		X.m_ulValue[0]=(unsigned long)(num-A);    

		while(X.m_ulValue[i]==0)
		{
			X.m_ulValue[i]=0xffffffff;
			i++;
		}
		X.m_ulValue[i]--;
		if(X.m_ulValue[i]==0)
			X.m_nLength--;
		Mov_Big_Big(Y,X);
	}
}

/****************************************************************************************
大数相乘
调用形式：Mul_Big_Big(Y,N,A)
返回值：X=N*A
	A	a 0
	N	c d
		0					d*0
		1			c*0 
					d*a
		2	c*a

****************************************************************************************/
void Mul_Big_Big(CBigInt *Y, CBigInt N, CBigInt A)
{
	CBigInt X;
	unsigned long long sum,mul=0,carry=0;
	unsigned int i,j;
	if(A.m_nLength==1)
		Mul_Big_Long(Y,N,A.m_ulValue[0]);
	else
	{
		CBigIntInit(&X);
		X.m_nLength=N.m_nLength+A.m_nLength-1;
		for(i=0;i<X.m_nLength;i++)
		{
			sum=carry;
			carry=0;
			for(j=0;j<A.m_nLength;j++)
			{
				if(((i-j)>=0)&&((i-j)<N.m_nLength))
				{
					mul=N.m_ulValue[i-j];
					mul*=A.m_ulValue[j];
					carry+=mul>>32;
					mul=mul&0xffffffff;
					sum+=mul;
				}
			}				
			carry+=sum>>32;
			X.m_ulValue[i]=(unsigned long)sum;
		}
		if(carry)
		{
			X.m_nLength++;
			X.m_ulValue[X.m_nLength-1]=(unsigned long)carry;
		}
		i = X.m_nLength-1;
		while(X.m_ulValue[i]==0 && i>0)
		{
			X.m_nLength--;
			i--;
		}
		Mov_Big_Big(Y,X);
	}
}

void Mul_Big_Long(CBigInt *Y, CBigInt N, unsigned long A)
{
	CBigInt X;
	unsigned long long mul;
	unsigned long carry=0;
	unsigned int i;
	CBigIntInit(&X);
	Mov_Big_Big(&X,N);;
	for(i=0;i<N.m_nLength;i++)
	{
		mul=N.m_ulValue[i];
		mul=mul*A+carry;
		X.m_ulValue[i]=(unsigned long)mul;
		carry=(unsigned long)(mul>>32);
	}
	if(carry)
	{
		X.m_nLength++;
		X.m_ulValue[X.m_nLength-1]=carry;
	}
	i = X.m_nLength-1;
	while(X.m_ulValue[i]==0 && i>0)
	{
		X.m_nLength--;
		i--;
	}
	Mov_Big_Big(Y,X);
}

/****************************************************************************************
大数相除
调用形式：Div_Big_Big(P,N,A)
返回值：P=N/A
****************************************************************************************/
void Div_Big_Big(CBigInt *M,CBigInt N, CBigInt A)
{
	CBigInt X,Y,Z,T;
	unsigned int i,len;
	unsigned long long num,div;
	if(A.m_nLength==1)
		Div_Big_Long(M,N,A.m_ulValue[0]);
	else
	{
		CBigIntInit(&X);
		CBigIntInit(&Y);
		CBigIntInit(&Z);
		CBigIntInit(&T);
		Mov_Big_Big(&Y,N);
		while(Cmp(Y,A)>=0)
		{        
			div=Y.m_ulValue[Y.m_nLength-1];
			num=A.m_ulValue[A.m_nLength-1];
			len=Y.m_nLength-A.m_nLength;
			if((div==num)&&(len==0))
			{
				//Mov_Big_Big(&X,Add_Big_Long(X,1));
				Add_Big_Long(&X,X,1);
				break;
			}
			if((div<=num)&&len)
			{
				len--;
				div=(div<<32)+Y.m_ulValue[Y.m_nLength-2];
			}
			div=div/(num+1);
			Mov_Big_Long(&Z,div);
			if(len)
			{
				Z.m_nLength+=len;
				for(i=Z.m_nLength-1;i>=len;i--)
					Z.m_ulValue[i]=Z.m_ulValue[i-len];
				for(i=0;i<len;i++)
					Z.m_ulValue[i]=0;
			}
			//Mov_Big_Big(&X,Add_Big_Big(X,Z));
			Add_Big_Big(&X,X,Z);
			//Mov_Big_Big(&Y,Sub_Big_Big(Y,Mul_Big_Big(A,Z)));
			Mul_Big_Big(&T,A,Z);
			Sub_Big_Big(&Y,Y,T);
		}
		Mov_Big_Big(M,X);
	}
}
/*
void Div_Big_Big(CBigInt *P, CBigInt N, CBigInt A)
{
	CBigInt X,Y,Z;
	unsigned int i,len;
	unsigned long long num,div;
	if(A.m_nLength==1)
		Div_Big_Long(P,N,A.m_ulValue[0]);//return Div_Big_Long(N,A.m_ulValue[0]);
	else
	{
		CBigIntInit(&X);
		//CBigIntInit(Y);
		CBigIntInit(&Z);
		Mov_Big_Big(&Y,N);
		while(Cmp(Y,A)>=0)
		{        
			div=Y.m_ulValue[Y.m_nLength-1];
			num=A.m_ulValue[A.m_nLength-1];
			len=Y.m_nLength-A.m_nLength;
			if((div==num)&&(len==0))
			{
				//Mov_Big_Big(X,Add_Big_Long(X,1));
				Add_Big_Long(&X,X,1);
				break;
			}
			if((div<=num)&&len)
			{
				len--;
				div=(div<<32)+Y.m_ulValue[Y.m_nLength-2];
			}
			div=div/(num+1);
			Mov_Big_Long(&Z,div);
			if(len)
			{
				Z.m_nLength+=len;
				for(i=Z.m_nLength-1;i>=len;i--)
					Z.m_ulValue[i]=Z.m_ulValue[i-len];
				for(i=0;i<len;i++)
					Z.m_ulValue[i]=0;
			}
			//Mov_Big_Big(X,Add_Big_Big(X,Z));
			Add_Big_Big(&X,X,Z);
			//Mov_Big_Big(Y,Sub_Big_Big(Y,Mul_Big_Big(A,Z)));
			Mul_Big_Big(&A,A,Z);
			Sub_Big_Big(&Y,Y,Y);
		}
		Mov_Big_Big(P,X);
	}
}
*/
void Div_Big_Long(CBigInt *Y, CBigInt N, unsigned long A)
{
	CBigInt X;
	unsigned long long div,mul;
	unsigned long carry=0;
	int i;
	//CBigIntInit(X);
	Mov_Big_Big(&X,N);;
	if(X.m_nLength==1)
	{
		X.m_ulValue[0]=X.m_ulValue[0]/A;
		Mov_Big_Big(Y,X);
	}
	else
	{
		for(i=X.m_nLength-1;i>=0;i--)
		{
			div=carry;
			div=(div<<32)+X.m_ulValue[i];
			X.m_ulValue[i]=(unsigned long)(div/A);
			mul=(div/A)*A;
			carry=(unsigned long)(div-mul);
		}
		if(X.m_ulValue[X.m_nLength-1]==0)
			X.m_nLength--;
		Mov_Big_Big(Y,X);
	}
}

/****************************************************************************************
大数求模
调用形式：Mod_Big_Big(Z,N,A)
返回值：Z=N%A
****************************************************************************************/
void Mod_Big_Big(CBigInt *Z,CBigInt N, CBigInt A)
{
	CBigInt X,Y;
	unsigned long long div,num;
	unsigned long carry=0;
	unsigned int i,len;
	CBigIntInit(&X);
	CBigIntInit(&Y);
	Mov_Big_Big(&X,N);;
	while(Cmp(X,A)>=0)
	{
		div=X.m_ulValue[X.m_nLength-1];
		num=A.m_ulValue[A.m_nLength-1];
		len=X.m_nLength-A.m_nLength;
		if((div==num)&&(len==0))
		{
			//Mov_Big_Big(&X,Sub_Big_Big(X,A));
			Sub_Big_Big(&X,X,A);
			break;
		}
		if((div<=num)&&len)
		{
			len--;div=(div<<32)+X.m_ulValue[X.m_nLength-2];
		}
		div=div/(num+1);
		Mov_Big_Long(&Y,div);		
		//Mov_Big_Big(&Y,Mul_Big_Big(A,Y));
		Mul_Big_Big(&Y,A,Y);
		if(len)
		{
			Y.m_nLength+=len;
			for(i=Y.m_nLength-1;i>=len;i--)
				Y.m_ulValue[i]=Y.m_ulValue[i-len];
			for(i=0;i<len;i++)
				Y.m_ulValue[i]=0;
		}
		//Mov_Big_Big(&X,Sub_Big_Big(X,Y));
		Sub_Big_Big(&X,X,Y);
	}
	Mov_Big_Big(Z,X);
}


unsigned long Mod_Big_Long(CBigInt N, unsigned long A)
{
	unsigned long long div;
	unsigned long carry=0;
	int i;
	if(N.m_nLength==1)
		return(N.m_ulValue[0]%A);


	for(i=N.m_nLength-1;i>=0;i--)
	{
		div=N.m_ulValue[i];
		div+=carry*0x100000000;
		carry=(unsigned long)(div%A);
	}
	return carry;
}


/****************************************************************************************
从字符串按10进制或16进制格式输入到大数
调用格式：Get(N,str,sys)
返回值：N被赋值为相应大数
sys暂时只能为10或16
****************************************************************************************/
void Get(CBigInt *N, char* str, unsigned int system)
{
	int i;
	char s[1024];
	int len,k;
	//CBigInt N;
	CBigIntInit(N);
	memset(s, 0x00, sizeof(s));
	strcpy(s, str);
	len = strlen(str);
	Mov_Big_Long(N,0);
	//for(i = len -1;i >= 0;i --)
	for(i = 0; i < len; i++)
	{
		Mul_Big_Long(N,*N,system);
		//Mov_Big_Big(N,Mul_Big_Long(N,system));
		if((s[i]>='0')&&(s[i]<='9'))
			k=s[i]-48;
		else 
			if((s[i]>='A')&&(s[i]<='F'))
				k=s[i]-55;
		else 
			if((s[i]>='a')&&(s[i]<='f'))
				k=s[i]-87;
		else k=0;
		//Mov_Big_Big(N,Add_Big_Long(N,k));
		Add_Big_Long(N,*N,k);
	}
	//return N;
}

/****************************************************************************************
将大数按10进制或16进制格式输出为字符串
调用格式：Put(N,str,sys)
返回值：无，参数str被赋值为N的sys进制字符串
sys暂时只能为10或16
****************************************************************************************/
char* Put(CBigInt N, unsigned int system)
{
	char* str;	
	char t[17]="0123456789ABCDEF";
	int i, a, len;
	char s[1024] = {"0"};
	char s1[1024] = {"0"};
	CBigInt X;
	str="";
	if((N.m_nLength==1)&&(N.m_ulValue[0]==0))
	{
		str="0";
		return str;
	}

	CBigIntInit(&X);
	Mov_Big_Big(&X,N);;
	for(i = 0; X.m_ulValue[X.m_nLength-1]>0; i ++)
	{
		a=Mod_Big_Long(X,system);
		s[i] = t[a]; 
		//Mov_Big_Big(&X,Div_Big_Long(X,system));
		Div_Big_Long(&X,X,system);
	}
	len = i-1;  
	for( i= 0; i<= len; i++)
		s1[i] = s[len-i];
	str = s1;
	return str;
}
//主要显示基域元素，将最低位为0的域元素补0显示
unsigned char* PutFieldElement(CBigInt N, unsigned int system)
{
	unsigned char *str;	
	char t[17]="0123456789ABCDEF";
	int i, a, len,offset;
	unsigned char s[1024] = {"0"};
	unsigned char s1[1024] = {"0"};
	CBigInt X;
	str = (unsigned char *)"";
	if((N.m_nLength==1)&&(N.m_ulValue[0]==0))
	{
		str = (unsigned char *)"0";
		return str;
	}

	CBigIntInit(&X);
	Mov_Big_Big(&X,N);;
	for(i = 0; X.m_ulValue[X.m_nLength-1]>0; i ++)
	{
		a=Mod_Big_Long(X,system);
		s[i] = t[a]; 
		//Mov_Big_Big(&X,Div_Big_Long(X,system));
		Div_Big_Long(&X,X,system);
	}
	len = i-1;
	offset = 63-len;   //主要是为了将最低位为0的域元素补0
	for( i= 0; i<= len; i++)
		s1[i+offset] = s[len-i];
	str = s1;
	return str;
}

/****************************************************************************************
求不定方程ax-by=1的最小整数解
调用方式：Euc(N,A)
返回值：Z,满足：NZ mod A=1
****************************************************************************************/
void Inv(CBigInt *Z, CBigInt N, CBigInt A)
{
	CBigInt M,E,X,Y,I,J;
	int x,y;	
	CBigIntInit(&M);
	CBigIntInit(&E);
	CBigIntInit(&X);
	CBigIntInit(&Y);
	CBigIntInit(&I);
	CBigIntInit(&J);
	if(Cmp(N,A)>=0)
		Mod_Big_Big(&N,N,A);
	Mov_Big_Big(&M,A);
	Mov_Big_Big(&E,N);
	Mov_Big_Long(&X,0);
	Mov_Big_Long(&Y,1);
	x=y=1;
	while((E.m_nLength!=1)||(E.m_ulValue[0]!=0))
	{
		//Mov_Big_Big(&I,Div_Big_Big(M,E));
		Div_Big_Big(&I,M,E);
		//Mov_Big_Big(&J,Mod_Big_Big(M,E));
		Mod_Big_Big(&J,M,E);
		Mov_Big_Big(&M,E);
		Mov_Big_Big(&E,J);
		Mov_Big_Big(&J,Y);
		//Mov_Big_Big(&Y,Mul_Big_Big(Y,I));
		Mul_Big_Big(&Y,Y,I);
		if(x==y)
		{
			if(Cmp(X,Y)>=0)
				Sub_Big_Big(&Y,X,Y); // Mov_Big_Big(&Y,Sub_Big_Big(X,Y));
			else
			{
				//Mov_Big_Big(&Y,Sub_Big_Big(Y,X));
				Sub_Big_Big(&Y,Y,X);
				y=0;
			}
		}
		else
		{
			//Mov_Big_Big(&Y,Add_Big_Big(X,Y));
			Add_Big_Big(&Y,X,Y);
			x=1-x;
			y=1-y;
		}
		Mov_Big_Big(&X,J);
	}
	if(x==0)
		Sub_Big_Big(&X,A,X);  // Mov_Big_Big(&X,Sub_Big_Big(A,X));
	if(Cmp(X,A)>= 0)
	    Mod_Big_Big(&X,X,A);
	Mov_Big_Big(Z,X);
}

/****************************************************************************************
求乘方的模
调用方式：Exp(N,A,B)
返回值：Z=N^A MOD B
****************************************************************************************/
void Exp(CBigInt *Z, CBigInt N, CBigInt A, CBigInt B)
{
	CBigInt X,Y,M;
	int i,j,k;
	unsigned int n;
	unsigned long num;
	k=A.m_nLength*32-32;
	num=A.m_ulValue[A.m_nLength-1];
	while(num)
	{
		num=num>>1;
		k++;
	}
	CBigIntInit(&X);
	CBigIntInit(&Y);
	CBigIntInit(&M);
	Mov_Big_Big(&X,N);;
	for(i=k-2;i>=0;i--)
	{
		//Mov_Big_Big(&Y,Mul_Big_Long(X,X.m_ulValue[X.m_nLength-1]));
		Mul_Big_Long(&Y,X,X.m_ulValue[X.m_nLength-1]);
		//Mov_Big_Big(&Y,Mod_Big_Big(Y,B));
		Mod_Big_Big(&Y,Y,B);
		for(n=1;n<X.m_nLength;n++)
		{          
			for(j=Y.m_nLength;j>0;j--)
				Y.m_ulValue[j]=Y.m_ulValue[j-1];
			Y.m_ulValue[0]=0;
			Y.m_nLength++;
			//Mov_Big_Big(&Y,Add_Big_Big(Y,Mul_Big_Long(X,X.m_ulValue[X.m_nLength-n-1])));
			Mul_Big_Long(&Y,X,X.m_ulValue[X.m_nLength-n-1]);
			//Mov_Big_Big(&Y,Mod_Big_Big(Y,B));
			Mod_Big_Big(&Y,Y,B);
		}
		Mov_Big_Big(&X,Y);
		if((A.m_ulValue[i>>5]>>(i&31))&1)
		{
			//Mov_Big_Big(&Y,Mul_Big_Long(N,X.m_ulValue[X.m_nLength-1]));
			Mul_Big_Long(&Y,N,X.m_ulValue[X.m_nLength-1]);
			//Mov_Big_Big(&Y,Mod_Big_Big(Y,B));
			Mod_Big_Big(&Y,Y,B);
			for(n=1;n<X.m_nLength;n++)
			{          
				for(j=Y.m_nLength;j>0;j--)
					Y.m_ulValue[j]=Y.m_ulValue[j-1];
				Y.m_ulValue[0]=0;
				Y.m_nLength++;
				//Mov_Big_Big(&Y,Add_Big_Big(Y,Mul_Big_Long(N,X.m_ulValue[X.m_nLength-n-1])));
				Mul_Big_Long(&M,N,X.m_ulValue[X.m_nLength-n-1]);
				Add_Big_Big(&Y,Y,M);
				//Mov_Big_Big(&Y,Mod_Big_Big(Y,B));
				Mod_Big_Big(&Y,Y,B);
			}
			Mov_Big_Big(&X,Y);
		}
	}
	Mov_Big_Big(Z,X);
}



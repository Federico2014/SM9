#include "utility.h"


//�������ֽ���������������
void Bytes_XOR(BYTE *b, BYTE *b1, BYTE *b2,unsigned int len)
{
	int i;
	for(i=0;i<len;i++)
		b[i] = b1[i]^b2[i];
}


/*
  K:256λ��MACֵ
  len1: Z���ֽ���
  len2: K2���ֽ���
*/
void MAC(BYTE *K,BYTE *Z, unsigned len1,BYTE *K2, int len2)
{
	int len;
	BYTE *msg;
	DWORD hash[8];
	len = len1 + len2;
	msg = (BYTE*)malloc(len);
	memcpy(msg,Z,len1);
	memcpy(&msg[len1],K2,len2);
	SM3_hash(msg, len, hash);
	SM3_Dword2byte(K,hash);
	free(msg);
}


//�ж������ֽ������Ƿ����
int Bytes_Equal(BYTE *b1, BYTE *b2,int len)
{
	int i=0;
	while(i<len)
	{
		if(b1[i]!=b2[i])
			return 0;
		i++;
	}
	return 1;
}


void printByte(BYTE* b,int len)
{
	int i;
	for(i = 0;i<len;i++)
		printf("%02X",b[i]);
}

//����Pת��Ϊ64���ֽڴ���ע��P��Ϊ�淶��
void PtoByte(BYTE *b,BNPoint P)
{
   unsigned char *str;
   str = PutFieldElement(P.x,HEX); 
   Hex2Byte(b, str, 64);
   str = PutFieldElement(P.y,HEX);
   Hex2Byte(&b[32], str, 64);
}


/*
  k�����ɵĹ�����Կ
  msg:������Ϣ���ֽ�ָ��
  msglen:������Ϣ���ֽڳ���
  klen : ��Ҫ��ȡ�Ĺ�����Կ�ı��س���
*/
void KDF(BYTE *k, BYTE *msg, unsigned int msgLength, unsigned int klen)
{
	unsigned int ct, v,len2;
	BYTE *Msg2,hash_byte[32]; 
	DWORD hash[8];
	unsigned int i,n,m,cur;
	ct = 1;              //��ʼ��������Ϊ1
	v = 256;             //SM3�������Ϊ256λ
	len2 = msgLength + 4;   //  H = Hv(Z||ct)
	Msg2 = (BYTE*)malloc(len2);
	memset(Msg2,0,len2);
	
	//memcpy(&Msg2,msg,msgLengh);
	for(i=0;i<msgLength;i++)
		Msg2[i] = msg[i];
	n = ceil((double)klen/v);
	m = klen - v*floor((double)klen/v);

	cur = 0;
 	for(i = 1;i<n;i++)
	{
		Msg2[len2-1] = ct;
		SM3_hash(Msg2, len2, hash);
	    SM3_Dword2byte(hash_byte,hash);
		memcpy(&k[cur],hash_byte,32);
		ct++;
		cur += 32;
	}	
	Msg2[len2-1] = ct;
	SM3_hash(Msg2, len2, hash);
	SM3_Dword2byte(hash_byte,hash);
	if(klen%v == 0)
		memcpy(&k[cur],hash_byte,32);	  
	else
	{
		memcpy(&k[cur],hash_byte,m/8);
	/*	m = m/8;
		for(i = 0;i<m;i++)
		{
			k[cur] = hash_byte[i];
		    cur++;
		}
		*/
	}

	free(Msg2);
}



/*
  h1����������ֵ
  msg:������Ϣ���ֽ�ָ��
  len:������Ϣ���ֽڳ���
  n : ͨ��Ϊ������N


*/
void Hash_1(CBigInt *h1, BYTE *msg, unsigned int len, CBigInt n)
{
	unsigned int ct, hlen,v, hlen_v,i,len2;
	BYTE *msg2; 
	DWORD hash[8],Ha[10];
	CBigInt HA,Mod;
	ct = 1;              //��ʼ��������Ϊ1
	v = 256;             //SM3�������Ϊ256λ
	len2 = len + 1 + 4;   //  H = Hv(0x01||Z||ct)
	msg2 = (BYTE*)malloc(len);
	memset(msg2,0,len2);
	msg2[0] = 0x01;
	memcpy(&msg2[1],msg,len);
	
	if(Cmp(n,BN.n)== 0)  //Hash_1���������nͨ��ΪN����Ⱥ�Ľ��� 
	{
		hlen = 320;      // heln = 8*ceil(5*(log_2 n)/32)
		hlen_v = 2;     // hlen_v = floor(hlen/v);		

		//memcpy(&msg2[len2-4],&ct,4);  //����ѭ��չ��
		msg2[len2-1] = 0x01;
	//	printf("msg2 = %s\n",msg2);
		SM3_hash(msg2, len2, hash);
		memcpy(Ha,hash,32);
		ct++;
		//memcpy(&msg2[len2-4],&ct,4);
	    msg2[len2-1] = 0x02;
	//	printf("msg2 = %s\n",msg2);
		SM3_hash(msg2, len2, hash);
		memcpy(&Ha[8],hash,8);               
		
		HA.m_nLength = 10;
		for(i = 0; i<10; i++)          // ��Ha��������ת��Ϊ����
			HA.m_ulValue[i] = Ha[9-i];
		i = HA.m_nLength-1;
    	while(HA.m_ulValue[i]==0 && i>0)
	    {
		   HA.m_nLength--;
		   i--;
	    }
		Sub_Big_Long(&Mod,BN.n,1);
		Mod_Big_Big(h1,HA,Mod);
		Add_Big_Long(h1,*h1,1);

	}else
		printf("Hash1�д���δ������쳣��");	

	//free(msg2);     //������׵��´���
}

void Hash_2(CBigInt *h1, BYTE *msg, unsigned int len, CBigInt n)
{
	unsigned int ct, hlen,v, hlen_v,i,len2;
	BYTE *msg2; 
	DWORD hash[8],Ha[10];
	CBigInt HA,Mod;
	ct = 1;              //��ʼ��������Ϊ1
	v = 256;             //SM3�������Ϊ256λ
	len2 = len + 1 + 4;   //  H = Hv(0x01||Z||ct)
	msg2 = (BYTE*)malloc(len);
	memset(msg2,0,len2);
	msg2[0] = 0x02;
	memcpy(&msg2[1],msg,len);
	
	if(Cmp(n,BN.n)== 0)  //Hash_1���������nͨ��ΪN����Ⱥ�Ľ��� 
	{
		hlen = 320;      // heln = 8*ceil(5*(log_2 n)/32)
		hlen_v = 2;     // hlen_v = floor(hlen/v);		

	  //����ѭ��չ��
		msg2[len2-1] = 0x01;
		SM3_hash(msg2, len2, hash);
		memcpy(Ha,hash,32);
		ct++;
	
	    msg2[len2-1] = 0x02;
		SM3_hash(msg2, len2, hash);
		memcpy(&Ha[8],hash,8);               
		
		HA.m_nLength = 10;
		for(i = 0; i<10; i++)          // ��Ha��������ת��Ϊ����
			HA.m_ulValue[i] = Ha[9-i];
		i = HA.m_nLength-1;
    	while(HA.m_ulValue[i]==0 && i>0)
	    {
		   HA.m_nLength--;
		   i--;
	    }
		Sub_Big_Long(&Mod,BN.n,1);
		Mod_Big_Big(h1,HA,Mod);
		Add_Big_Long(h1,*h1,1);

	}else
		printf("Hash1�д���δ������쳣��");	

//	free(msg2);              //������׵��´���
}

/*
��12������Ԫ��ת��ΪBYTE���飬�õ���СΪ384�ֽڴ�С��msg

void F12toByte(BYTE *msg,BNField12 b)
{
   char *str;
   str = Put(b.sq.im.im,HEX); 
   Hex2Byte(msg, (BYTE*)str, 64);
   str = Put(b.sq.im.re,HEX);
   Hex2Byte(&msg[32], (BYTE*)str, 64);
   str = Put(b.sq.re.im,HEX);
   Hex2Byte(&msg[64], (BYTE*)str, 64);
   str = Put(b.sq.re.re,HEX);
   Hex2Byte(&msg[96], (BYTE*)str, 64);
   str = Put(b.im.im.im,HEX);
   Hex2Byte(&msg[128], (BYTE*)str, 64);
   str = Put(b.im.im.re,HEX);
   Hex2Byte(&msg[160], (BYTE*)str, 64);
   str = Put(b.im.re.im,HEX);
   Hex2Byte(&msg[192], (BYTE*)str, 64);
   str = Put(b.im.re.re,HEX);
   Hex2Byte(&msg[224], (BYTE*)str, 64);
   str = Put(b.re.im.im,HEX);
   Hex2Byte(&msg[256], (BYTE*)str, 64);
   str = Put(b.re.im.re,HEX);
   Hex2Byte(&msg[288], (BYTE*)str, 64);
   str = Put(b.re.re.im,HEX);
   Hex2Byte(&msg[320], (BYTE*)str, 64);
   str = Put(b.re.re.re,HEX);
   Hex2Byte(&msg[352], (BYTE*)str, 64);
}
*/
void F12toByte(BYTE *msg,BNField12 b)
{
   unsigned char *str;
   str = PutFieldElement(b.sq.im.im,HEX); 
   Hex2Byte(msg, str, 64);
   str = PutFieldElement(b.sq.im.re,HEX);
   Hex2Byte(&msg[32], str, 64);
   str = PutFieldElement(b.sq.re.im,HEX);
   Hex2Byte(&msg[64], str, 64);
   str = PutFieldElement(b.sq.re.re,HEX);
   Hex2Byte(&msg[96], str, 64);
   str = PutFieldElement(b.im.im.im,HEX);
   Hex2Byte(&msg[128], str, 64);
   str = PutFieldElement(b.im.im.re,HEX);
   Hex2Byte(&msg[160], str, 64);
   str = PutFieldElement(b.im.re.im,HEX);
   Hex2Byte(&msg[192], str, 64);
   str = PutFieldElement(b.im.re.re,HEX);
   Hex2Byte(&msg[224], str, 64);
   str = PutFieldElement(b.re.im.im,HEX);
   Hex2Byte(&msg[256], str, 64);
   str = PutFieldElement(b.re.im.re,HEX);
   Hex2Byte(&msg[288], (BYTE*)str, 64);
   str = PutFieldElement(b.re.re.im,HEX);
   Hex2Byte(&msg[320], str, 64);
   str = PutFieldElement(b.re.re.re,HEX);
   Hex2Byte(&msg[352], str, 64);
}



//��16�����ַ���ת��ΪBYTE���飬ע��length��ҪΪż����ת����msg�ĳ���Ϊlenth/2
void Hex2Byte(BYTE *msg, BYTE *hex, int length)
{
	int len,i,j,k;
	len = length/2;
	for (i = 0; i < len; i++)
	{
		j = 2*i;
		if((hex[j]>='0')&&(hex[j]<='9'))
			msg[i] = hex[j]-48;
		else if((hex[j]>='A')&&(hex[j]<='F'))
				msg[i]=hex[j]-55;
		else if((hex[j]>='a')&&(hex[j]<='f'))
				msg[i] = hex[j]-87;
		else 
		    	msg[i] = 0;
		msg[i]*= 16;
		k = j + 1;
		if((hex[k]>='0')&&(hex[k]<='9'))
		    	msg[i] += (hex[k]-48);
		else if((hex[k]>='A')&&(hex[k]<='F'))
				msg[i] += (hex[k]-55);
		else if((hex[k]>='a')&&(hex[k]<='f'))
				msg[i] += (hex[k]-87);
	
	}
}

void CBigInt_substract_modN(CBigInt *X, CBigInt a, CBigInt b)
{
	CBigInt c,div;
	if(Cmp(a,b)>=0)
	{
		Sub_Big_Big(&c,a,b);  //
		if(Cmp(c,BN.n)>=0 )
	      Mod_Big_Big(&c,c,BN.n);
	}
    else
	{
		//
		Sub_Big_Big(&c,b,a);		
		Div_Big_Big(&div,c,BN.n);
		Add_Big_Long(&div,div,1);
		Mul_Big_Big(&div,div,BN.n);
		Sub_Big_Big(&c,div,c);
		if(Cmp(c,BN.n)==0)
			Mov_Big_Long(&c,0);
	}

	Mov_Big_Big(X,c);
}

/*

void Hash_1(CBigInt *h1, BYTE *msg, unsigned int len, CBigInt n)
{
	unsigned int ct, hlen,v, hlen_v,i,len2;
	BYTE *msg2; 
	DWORD hash[8],Ha[10];
	CBigInt HA,Mod;
	ct = 1;              //��ʼ��������Ϊ1
	v = 256;             //SM3�������Ϊ256λ
	len2 = len + 1 + 4;   //  H = Hv(0x01||Z||ct)
	msg2 = (BYTE*)malloc(len);
	memset(msg2,0,len2);
	msg2[0] = 0x01;
	memcpy(&msg2[1],msg,len);
	
	if(Cmp(n,BN.n)== 0)  //Hash_1���������nͨ��ΪN����Ⱥ�Ľ��� 
	{
		hlen = 320;      // heln = 8*ceil(5*(log_2 n)/32)
		hlen_v = 2;     // hlen_v = floor(hlen/v);		

		//memcpy(&msg2[len2-4],&ct,4);  //����ѭ��չ��
		msg2[len2-1] = 0x01;
		printf("msg2 = %s\n",msg2);
		SM3_hash(msg2, len2, hash);
		memcpy(Ha,hash,32);
		//ct++;
		//memcpy(&msg2[len2-4],&ct,4);
	    msg2[len2-1] = 0x02;
		printf("msg2 = %s\n",msg2);
		SM3_hash(msg2, len2, hash);
		memcpy(&Ha[8],hash,8);               
		
		HA.m_nLength = 10;
		for(i = 0; i<10; i++)          // ��Ha��������ת��Ϊ����
			HA.m_ulValue[i] = Ha[9-i];
		i = HA.m_nLength-1;
    	while(HA.m_ulValue[i]==0 && i>0)
	    {
		   HA.m_nLength--;
		   i--;
	    }
		Sub_Big_Long(&Mod,BN.n,1);
		Mod_Big_Big(h1,HA,Mod);
		Add_Big_Long(h1,*h1,1);

	}else
		printf("Hash1�д���δ������쳣��");	


}

*/
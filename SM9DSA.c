#include "SM9DSA.h"


void DSA_Demo()
{
	CBigInt a,b,c,d,e,f,ks,h,h2;
	BNField2 b1,b2;
	BNPoint2 P2,P_pub_s;
	BNPoint P1,dsA,S;

	BYTE id[]="Alice";
	BYTE M[] = "Chinese IBS standard";
	int sign;
	clock_t start,finish;
	double time1,time2,time3;

	Get(&a,"93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD",HEX);
	Get(&b,"21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616",HEX);
	Get(&c,"85AEF3D078640C98597B6027B441A01FF1DD2C190F5E93C454806C11D8806141",HEX);
	Get(&d,"3722755292130B08D2AAB97FD34EC120EE265948D19C17ABF9B7213BAF82D65B",HEX);
	Get(&e,"17509B092E845C1266BA0D262CBEE6ED0736A96FA347C8BD856DC76B84EBEB96",HEX);
	Get(&f,"A7CF28D519BE3DA65F3170153D278FF247EFBA98A71A08116215BBA5C999A7C7",HEX);

    P_construct_xy(&P1,a,b);
	F2_construct(&b1,d,c);
	F2_construct(&b2,f,e);    
    P2_construct_xy(&P2,b1,b2);
    
	
	//��Կ���ɽ׶�
	Get(&ks,"0130E78459D78545CB54C587E02CF480CE0B66340F319F348A1D5B1F2DC5F4",HEX);
	P2_multiply(&P_pub_s,P2,ks);
	P2_normorlize(&P_pub_s,P_pub_s);
	start = clock();
	DSA_Keygen(&dsA,ks,id,P1);
	finish = clock();
	time1 = (double)(finish-start);
	P_normorlize(&dsA,dsA);
    //����ǩ���׶�
	start = clock();
	DSA_Sign(&h, &S, M, P1, P_pub_s, dsA);
	finish = clock();
	time2 = (double)(finish-start);
	//����ǩ����֤�׶�
	start = clock();
	sign = DSA_Verify(&h2, h, S, M, id, P1, P2, P_pub_s);
	finish = clock();	
	time3 = (double)(finish-start);
	printf("\n********************************************\n");
	printf("*********SM9 ����ǩ���㷨ʵ����ʾ*********** \n");
	printf("********************************************\n");
	printf("***********************\n");
	printf("****1����Կ���ɽ׶�****\n");
	printf("***********************\n");
	printf("G1����ԪP1 = \n");
	P_toString(P1,HEX);
	printf("G2����ԪP2 = \n");
	P2_toString(P2,HEX);
	printf("ǩ����˽Կks = %s\n",Put(ks,HEX));
	printf("ǩ������Կ P_pub_s = [ks]P2 = \n");
	P2_toString(P_pub_s,HEX);
	printf("ʵ��A�ı�ʶIDA: %s\n",id);
	printf("ǩ��˽ԿdsA = \n");
	P_toString(dsA,HEX);
	printf("\n***********************\n");
	printf("****2������ǩ���׶�****\n");
	printf("***********************\n");
	printf("��ǩ������ϢM: %s\n",M);
	printf("��ϢM��ǩ��Ϊ��h,S��: \n");
	printf("h = %s\n",Put(h,HEX));
	printf("S = \n");
	P_toString(S,HEX);
	printf("\n***************************\n");
	printf("****3������ǩ����֤�׶�****\n");
	printf("***************************\n");
	printf("h2 = %s\n",Put(h2,HEX));
	if(sign)
		printf("h2 = h, ǩ����֤�ܹ���\n");
	else
		printf("h2 != h, ǩ����֤ʧ�ܣ�\n");

	printf("\nSM9 ����ǩ����Կ����ʱ�䣺%f ms\n",time1);
	printf("SM9 ����ǩ��ʱ�䣺%f ms\n",time2);
	printf("SM9 ����ǩ����֤ʱ�䣺%f ms\n",time3);
}
/*
   dsA:���ɵ�ôԿ
   ks:��˽Կ
   ID:���ID�ַ���
   P1��ȺG1������Ԫ

*/
void DSA_Keygen(BNPoint *dsA,CBigInt ks, BYTE *ID,BNPoint P1)
{
	int len;
	BYTE *msg;
	BYTE hid = 0x01;
	CBigInt t1,t2;
	len = strlen((const char*)ID);
	len +=1;
	msg = (BYTE*)malloc(len);
	memcpy(msg,ID,len-1);
	msg[len-1] = hid;
	Hash_1(&t1, msg, len, BN.n);
	Add_Big_Big(&t1,t1,ks);
	while(Cmp(t1,BN.ZERO)==0)
	{
		//ks = rand();
		Hash_1(&t1, msg, len, BN.n);
	    Add_Big_Big(&t1,t1,ks);
	}
	Inv(&t2,t1,BN.n);
	Mul_Big_Big(&t2,t2,ks);
	if(Cmp(t2,BN.n)>=0)
		Mod_Big_Big(&t2,t2,BN.n);
	P_multiply(dsA,P1,t2);
	free(msg);
}
/*
 h,S:���ɵ�����ǩ��
 M����ǩ����������Ϣ
 P1����������
 P_pub:��Կ
 dsA:ǩ��˽Կ
*/
void DSA_Sign(CBigInt *h, BNPoint *S, BYTE *M, BNPoint P1, BNPoint2 P_pub, BNPoint dsA)
{
	BNField12 g,w;
	CBigInt r,l;
	unsigned int len1,len2;
	BYTE *msg;
	Pairing_opt(&g,P_pub,P1);
	Get(&r,"033C8616B06704813203DFD00965022ED15975C662337AED648835DC4B1CBE",HEX);  //r=rand();
	//printf("r = %s\n",Put(r,HEX));
	F12_exp(&w,g,r);
	//F12_toString(g,HEX);
	//F12_toString(w,HEX);
	len1 = strlen((const char*)M);
	len2 = len1 + 384;  // һ��12������Ԫ����Ҫ 32*12 = 384 ���ֽ�
	msg = (BYTE*)malloc(len2);
	memcpy(msg,M,len1);
	F12toByte(&msg[len1],w);
	Hash_2(h, msg, len2, BN.n);
	CBigInt_substract_modN(&l,r,*h);
	P_multiply(S,dsA,l);
	P_normorlize(S,*S);
	free(msg);
}

int DSA_Verify(CBigInt *h2, CBigInt h, BNPoint S, BYTE *M, BYTE *ID,BNPoint P1, BNPoint2 P2, BNPoint2 P_pub)
{
	BNField12 g,t,u,w;
	BYTE *msg1,*msg2;
	BYTE hid = 0x01;
	int len1,len2;
	CBigInt h1;
	BNPoint2 P;

	if( Cmp(h,BN.n)>=0 || Cmp(h,BN.ONE)<=0)
		return 0;
	Pairing_opt(&g,P_pub,P1);
	F12_exp(&t,g,h);
	len1 = strlen((const char*)ID);
	len1 +=1;
	msg1 = (BYTE*)malloc(len1);
	memcpy(msg1,ID,len1-1);
	msg1[len1-1] = hid;
	Hash_1(&h1, msg1, len1, BN.n);
	P2_multiply(&P,P2,h1);
	P2_add(&P,P,P_pub);
	Pairing_opt(&u,P,S);
	F12_multiply(&w,u,t);

	len1 = strlen((const char*)M);
	len2 = len1 + 384;  // һ��12������Ԫ����Ҫ 32*12 = 384 ���ֽ�
	msg2 = (BYTE*)malloc(len2);
	memcpy(msg2,M,len1);
	F12toByte(&msg2[len1],w);
	Hash_2(h2, msg2, len2, BN.n);
	
	free(msg1);
	free(msg2);
	return Cmp(*h2,h)==0 ? 1 : 0;
}
#include "SM9KA.h"

void KA_Demo()
{
	CBigInt a,b,c,d,e,f;
	CBigInt ke,t1,t1_inv,t2,t3,t3_inv,t4,rA,rB;
	BNField2 b1,b2;
	BNPoint2 P2,deA,deB;
	BNPoint P1,P_pub_e,QA,QB,RA,RB;
	BNField12 g1,g2,g3,g1_,g2_,g3_;
	BYTE hid = 0x02;
	BYTE IDA[]="Alice";
	BYTE IDB[]="Bob";
	BYTE *msg1,*msg2,*msg3,*SKB,*msg4,hash_byte[32],SB[32],hash_byte1[32];
	BYTE *msg_SB,S1[32],*SKA,SA[32],S2[32];
	unsigned int len1,len2,klen,length,cur,len4,SB_len;
	DWORD hash[8];
	clock_t start,finish;
	double time1,time2;

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

	//系统主密钥及加密密钥生成
	start = clock();
	Get(&ke,"02E65B0762D042F51F0D23542B13ED8CFA2E9A0E7206361E013A283905E31F",HEX);  //加密主私钥
	P_multiply(&P_pub_e,P1,ke);                                //加密主公钥
	P_normorlize(&P_pub_e,P_pub_e);
	len1 = strlen((const char*)IDA);
	len1 +=1;
	msg1 = (BYTE*)malloc(len1);
	memcpy(msg1,IDA,len1-1);
	msg1[len1-1] = hid;
	Hash_1(&t1, msg1, len1, BN.n);
	Add_Big_Big(&t1,t1,ke);            //t1在有限域FN中，若大于N需要约化
	while(Cmp(t1,BN.ZERO)==0)
	{
		//需要调用随机数重新生成主私钥和公钥
	}
	Inv(&t1_inv,t1,BN.n);
	Mul_Big_Big(&t2,t1_inv,ke);
	if(Cmp(t2,BN.n)>=0)
		Mod_Big_Big(&t2,t2,BN.n);
	P2_multiply(&deA,P2,t2);
	P2_normorlize(&deA,deA);
	len2 = strlen((const char*)IDB);
	len2 +=1;
	msg2 = (BYTE*)malloc(len2);
	memcpy(msg2,IDB,len2-1);
	msg2[len2-1] = hid;
	Hash_1(&t3, msg2, len2, BN.n);
	Add_Big_Big(&t3,t3,ke);          //t3在有限域FN中，若大于N需要约化
	while(Cmp(t1,BN.ZERO)==0)
	{
		//需要调用随机数重新生成主私钥和公钥
	}
	Inv(&t3_inv,t3,BN.n);
	Mul_Big_Big(&t4,t3_inv,ke);
	if(Cmp(t4,BN.n)>=0)
		Mod_Big_Big(&t4,t4,BN.n);
	P2_multiply(&deB,P2,t4);
	P2_normorlize(&deB,deB);
	klen = 0x80;
	SKB = (BYTE*)malloc(klen);
	finish = clock();
	time1 = (double)(finish-start);

	//密钥交换协议阶段");
	// A1-A4步骤
	start = clock();
	Hash_1(&t3, msg2, len2, BN.n);
	P_multiply(&QB,P1,t3);
	P_add(&QB,QB,P_pub_e);
	Get(&rA,"5879DD1D51E175946F23B1B41E93BA31C584AE59A426EC1046A4D03B06C8",HEX);  //随机数rA
	P_multiply(&RA,QB,rA);
	P_normorlize(&RA,RA);

	// B1-B7步骤
	Hash_1(&t1, msg1, len1, BN.n);
	P_multiply(&QA,P1,t1);
	P_add(&QA,QA,P_pub_e);
	Get(&rB,"018B98C44BEF9F8537FB7D071B2C928B3BC65BD3D69E1EEE213564905634FE",HEX);  //随机数rA
	P_multiply(&RB,QA,rB);
	P_normorlize(&RB,RB);
	if(!P_isOnBNCurve(RA))
	{
	    printf("*********密钥交换协议 B4 步骤验证失败***********\n");
		exit(0);
	}
	Pairing_opt(&g1,deB,RA);
	Pairing_opt(&g2,P2,P_pub_e);
	F12_exp(&g2,g2,rB);
	F12_exp(&g3,g1,rB);
	length = len1 + len2 - 2; //IDA和IDB的字节长度
	length += 64*2;        //加上RA和RB的字节长度
	length += 384*3;    // 加上g1,g2,g3的字节长度，每个12扩域元素需要12*32 = 284个字节
    msg3 = (BYTE*)malloc(length);
	cur = 0;
	memcpy(msg3,IDA,len1-1);
	cur += len1-1;
	memcpy(&msg3[cur],IDB,len2-1);
	cur += len2-1;
	PtoByte(&msg3[cur],RA);
	cur += 64;
	PtoByte(&msg3[cur],RB);
	cur +=64;
	F12toByte(&msg3[cur],g1);
	cur +=384;
	F12toByte(&msg3[cur],g2);
	cur +=384;
	F12toByte(&msg3[cur],g3);
	KDF(SKB, msg3, length, klen);
	//选项，计算Hash(g2||g3||IDA||IDB||RA||RB),注意该Hash采用SM3算法
	len4 = length - 384;
	msg4 = (BYTE*)malloc(len4);
	cur = 0;
	F12toByte(&msg4[cur],g2);
	cur += 384;
	F12toByte(&msg4[cur],g3);
	cur += 384;
	memcpy(&msg4[cur],IDA,len1-1);
	cur += len1-1;
	memcpy(&msg4[cur],IDB,len2-1);
	cur += len2-1;
	PtoByte(&msg4[cur],RA);
	cur += 64;
	PtoByte(&msg4[cur],RB);
	SM3_hash(msg4, len4, hash);
	SM3_Dword2byte(hash_byte,hash);
	//选项计算，计算SB = Hash(0x82||g1||Hash(g2||g3||IDA||IDB||RA||RB))
	SB_len = 1 + 384 + 32;
	msg_SB = (BYTE*)malloc(SB_len);
	msg_SB[0] = 0x82;
	F12toByte(&msg_SB[1],g1);
    memcpy(&msg_SB[385],hash_byte,32);
	SM3_hash(msg_SB, SB_len, hash);
	SM3_Dword2byte(SB,hash);
	// A5-A8步骤
	if(!P_isOnBNCurve(RB))
	{
	    printf("*********密钥交换协议 A5 步骤验证失败***********\n");
		exit(0);
	}
	Pairing_opt(&g1_,P2,P_pub_e);
	F12_exp(&g1_,g1_,rA);
	Pairing_opt(&g2_,deA,RB);
	F12_exp(&g3_,g2_,rA);
	//选项，计算Hash(g2_||g3_||IDA||IDB||RA||RB),注意该Hash采用SM3算法
	cur = 0;
	F12toByte(&msg4[cur],g2_);
	cur += 384;
	F12toByte(&msg4[cur],g3_);
	cur += 384;
	memcpy(&msg4[cur],IDA,len1-1);
	cur += len1-1;
	memcpy(&msg4[cur],IDB,len2-1);
	cur += len2-1;
	PtoByte(&msg4[cur],RA);
	cur += 64;
	PtoByte(&msg4[cur],RB);
	SM3_hash(msg4, len4, hash);
	SM3_Dword2byte(hash_byte1,hash);
   //选项计算，计算S1 = Hash(0x82||g1_||Hash(g2_||g3_||IDA||IDB||RA||RB))
	msg_SB[0] = 0x82;
	F12toByte(&msg_SB[1],g1_);
    memcpy(&msg_SB[385],hash_byte1,32);
	SM3_hash(msg_SB, SB_len, hash);
	SM3_Dword2byte(S1,hash);
	//计算SKA
	SKA = (BYTE*)malloc(klen);
	cur = 0;
	memcpy(msg3,IDA,len1-1);
	cur += len1-1;
	memcpy(&msg3[cur],IDB,len2-1);
	cur += len2-1;
	PtoByte(&msg3[cur],RA);
	cur += 64;
	PtoByte(&msg3[cur],RB);
	cur +=64;
	F12toByte(&msg3[cur],g1_);
	cur +=384;
	F12toByte(&msg3[cur],g2_);
	cur +=384;
	F12toByte(&msg3[cur],g3_);
	KDF(SKA, msg3, length, klen);
	//计算SA
	msg_SB[0] = 0x83;
	SM3_hash(msg_SB, SB_len, hash);
	SM3_Dword2byte(SA,hash);
	//B8步骤，计算S2	
	F12toByte(&msg_SB[1],g1);
    memcpy(&msg_SB[385],hash_byte,32);
	SM3_hash(msg_SB, SB_len, hash);
	SM3_Dword2byte(S2,hash);
	finish = clock();
	time2 = (double)(finish - start);

	printf("\n********************************************\n");
	printf("*********SM9 密钥交换协议实例演示***********\n");
	printf("********************************************\n");
	printf("***********************************\n");
	printf("****1、系统主密钥及加密密钥生成****\n");
	printf("***********************************\n");
	printf("G1生成元P1 = \n");
	P_toString(P1,HEX);
	printf("G2生成元P2 = \n");
	P2_toString(P2,HEX);
	printf("KGC主私钥ke = %s\n",Put(ke,HEX));
	printf("KGC主公钥 P_pub_e = [ke]P1 = \n");
	P_toString(P_pub_e,HEX);

	printf("实体A的标识: %s\n",IDA);
	printf("t1 = H1(IDA||hid,N) + ke:\n %s\n",Put(t1,HEX));
	printf("t2 = ke * t1^(-1):\n %s\n",Put(t2,HEX));
	printf("deA = [t2]P2\n");
	P2_toString(deA,HEX);

	printf("实体B的标识: %s\n",IDB);
	printf("t3 = H1(IDB||hid,N) + ke:\n %s\n",Put(t3,HEX));
	printf("t4 = ke * t3^(-1):\n %s\n",Put(t4,HEX));
	printf("deB = [t4]P2\n");
	P2_toString(deB,HEX);

	printf("***********************************\n");
	printf("**********2、密钥交换协议**********\n");
	printf("***********************************\n");
	printf("*****A1-A4步骤*****\n");
	printf("QB = [H1(IDB||hid,N)]P1 + P_pub_e:\n");
	P_toString(QB,HEX);
	printf("rA = %s\n",Put(rA,HEX));
	printf("RA = [rA]QB = \n");
	P_toString(RA,HEX);

	printf("*****B1-B7步骤*****\n");
	printf("QA = [H1(IDA||hid,N)]P1 + P_pub_e:\n");
	P_toString(QA,HEX);
	printf("rB = %s\n",Put(rB,HEX));
	printf("RB = [rB]QA = \n");
	P_toString(RB,HEX);
	printf("g1 = e(RA,deB)\n");
	F12_toString(g1,HEX);
	printf("g2 = e(P_pub-e,P2)^rB\n");
	F12_toString(g2,HEX);
	printf("g3 = g1^rB\n");
	F12_toString(g3,HEX);
	printf("SKB = KDF(IDA||IDB||RA||RB||g1||g2||g3,klen):\n");
	printByte(SKB,klen/8);
	printf("\nHash(g2||g3||IDA||IDB||RA||RB):\n");
    printByte(hash_byte,256/8);
	printf("\nSB = Hash(0x82||g1||Hash(g2||g3||IDA||IDB||RA||RB)):\n");
    printByte(SB,32);
	printf("\n*****A5-A8步骤*****\n");
	printf("g1_ = e(P_pub_e,P2)^rA\n");
	F12_toString(g1_,HEX);
	printf("g2_ = e(RB,deA)^rB\n");
	F12_toString(g2_,HEX);
	printf("g3_ = g2_^rA\n");
	F12_toString(g3_,HEX);
	printf("\nHash(g2_||g3_||IDA||IDB||RA||RB):\n");
    printByte(hash_byte1,256/8);
	printf("\nS1 = Hash(0x82||g1_||Hash(g2_||g3_||IDA||IDB||RA||RB)):\n");
    printByte(S1,32);
	if(Bytes_Equal(SB,S1,32))
		printf("\nS1=SB, A6步骤验证通过！\n");
	else
	{
		printf("\nS1!=SB, A6步骤验证失败！\n");
		exit(0);
	}
	printf("SKA = KDF(IDA||IDB||RA||RB||g1_||g2_||g3_,klen):\n");
	printByte(SKA,klen/8);
	printf("\nSA = Hash(0x83||g1_||Hash(g2_||g3_||IDA||IDB||RA||RB)):\n");
    printByte(SA,32);
    printf("\n*****B8步骤*****\n");
	printf("S2 = Hash(0x83||g1||Hash(g2||g3||IDA||IDB||RA||RB)):\n");
    printByte(S2,32);
	if(Bytes_Equal(S2,SA,32))
		printf("\nS2=SA, B8步骤验证通过！\n");
	else
	{
		printf("\nS2!=SA, B8步骤验证失败！\n");
		exit(0);
	}
	
	printf("SM9 密钥交换协议系统主密钥及加密密钥生成时间：%f ms\n",time1);
	printf("SM9 密钥交换协议时间：%f ms\n",time2);

	free(msg1);
	free(msg2);
	free(msg3);
	free(SKB);
	free(msg4);
	free(msg_SB);
	free(SKA);
}
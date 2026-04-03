#include "sm9/sm9/sm9_pkc.h"


void KEM_demo()
{
	CBigInt a,b,c,d,e,f,ke;
	BNField2 b1,b2;
	BNPoint2 P2,deB;
	BNPoint P1,P_pub_e,C;

	BYTE id[]="Bob";
	BYTE *K,*K_;

	unsigned int klen;
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

	// Key generation phase
	Get(&ke,"01EDEE3778F441F8DEA3D9FA0ACC4E07EE36C93F9A08618AF4AD85CEDE1C22",HEX);
	P_multiply(&P_pub_e,P1,ke);
	P_normorlize(&P_pub_e,P_pub_e);
	start = clock();
	PKC_Keygen(&deB,ke,id,P2);
	P2_normorlize(&deB,deB);
	finish = clock();
	time1 = (double)(finish-start);
	klen = 0x0100;
	K = (BYTE *)malloc(klen/8);
    K_ = (BYTE *)malloc(klen/8);
	start = clock();
	PKC_kem(K,&C,id,P1,P2,P_pub_e,klen);
	finish = clock();
	time2 = (double)(finish-start);
	start = clock();
	PKC_kom(K_, C, deB, id, klen);
	finish = clock();
	time3 = (double)(finish-start);
	printf("\n********************************************\n");
	printf("*********SM9 Key Encapsulation Demo*********** \n");
	printf("********************************************\n");
	printf("***************************************\n");
	printf("****1. System master key and user key generation****\n");
	printf("***************************************\n");
	printf("Generator P1 in G1 = \n");
	P_toString(P1,HEX);
	printf("Generator P2 in G2 = \n");
	P2_toString(P2,HEX);
	printf("KGC private key ke = %s\n",Put(ke,HEX));
	printf("KGC public key P_pub_e = [ke]P1 = \n");
	P_toString(P_pub_e,HEX);
	printf("Entity B identifier IDB: %s\n",id);
	printf("Entity B private key deB = \n");
	P2_toString(deB,HEX);
	printf("Encapsulated key length: %x\n",klen);
	printf("\n************************************\n");
	printf("**************2. Key encapsulation phase*******\n");
	printf("************************************\n");
	printf("Encapsulated ciphertext C = \n");
	P_toString(C,HEX);
	printf("Encapsulated key K = \n");
	printByte(K,klen/8);
	printf("\n************************************\n");
	printf("**************3. Key decapsulation phase*****\n");
	printf("************************************\n");
	printf("Decapsulated key K_ = \n");
	printByte(K_,klen/8);

	printf("\nSM9 master key and user key generation time: %f ms\n",time1);
	printf("SM9 key encapsulation time: %f ms\n",time2);
	printf("SM9 key decapsulation time: %f ms\n",time3);
	free(K);
	free(K_);
}

/*
  mode: 0 = encrypt with stream mode, 1 = encrypt with block mode
*/
void PKC_demo(int mode)
{
	CBigInt a,b,c,d,e,f,ke;
	BNField2 b1,b2;
	BNPoint2 P2,deB;
	BNPoint P1,P_pub_e,C1;
	BNField12 w;

	BYTE id[] = "Bob";
	BYTE M[] = "Chinese IBE standard";
	BYTE *K,*K1,*K2,*C2,*C3,*msg,*K_,*K1_,*K2_;
	BYTE *M_,*u,*m;
	unsigned int K1_len,K2_len,mlen,len,klen,idLen;
    sm4_context ctx;
	BYTE input[32];
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

	// Key generation phase
	Get(&ke,"01EDEE3778F441F8DEA3D9FA0ACC4E07EE36C93F9A08618AF4AD85CEDE1C22",HEX);
	P_multiply(&P_pub_e,P1,ke);
	P_normorlize(&P_pub_e,P_pub_e);
	start = clock();
	PKC_Keygen(&deB,ke,id,P2);
	P2_normorlize(&deB,deB);
	finish = clock();
	time1 = (double)(finish-start);
	K2_len = 0x0100;
	idLen = strlen((const char*)id);
	mlen = strlen((const char*)M);
    // Encryption phase
	start = clock();
	if(mode==0)          // Stream mode encryption
	{
		K2_len = K2_len/8;            // Convert to bytes
	    klen = (mlen+K2_len)*8;
        K = (BYTE *)malloc(klen/8);
	    PKC_kem(K,&C1,id,P1,P2,P_pub_e,klen);
		K1 = (BYTE *)malloc(mlen);
		memcpy(K1,K,mlen);
	    K2 = (BYTE *)malloc(K2_len);
		memcpy(K2,&K[mlen],K2_len);
		C2 = (BYTE *)malloc(mlen);
		Bytes_XOR(C2,K1, M,mlen);
		C3 = (BYTE *)malloc(32);
		MAC(C3, C2,mlen,K2,K2_len);

	}else                    // Block mode encryption
	{
		K1_len = 0x80;
		klen = K1_len + K2_len;
        K = (BYTE *)malloc(klen/8);
	    PKC_kem(K,&C1,id,P1,P2,P_pub_e,klen);
		K1_len = K1_len/8;
		K2_len = K2_len/8;
		K1 = (BYTE *)malloc(K1_len);
		memcpy(K1,K,K1_len);
        K2 = (BYTE *)malloc(K2_len);
		memcpy(K2,&K[K1_len],K2_len);
	    // sm4 encryption
		memcpy(input,M,mlen);
		memset(&input[mlen],0x0C,32-mlen);
		C2 = (BYTE *)malloc(32);
	    sm4_setkey_enc(&ctx,K1);
	    sm4_crypt_ecb(&ctx,1,32,input,C2);
		C3 = (BYTE *)malloc(32);
		MAC(C3, C2,32,K2,K2_len);
	}
	finish = clock();
	time2 = (double)(finish-start);

 	// Decryption phase
	start = clock();
	if(mode==0)                 // Stream mode decryption
	{
		Pairing_opt(&w,deB,C1);
        len = 64 + 384 + idLen;
	    msg = (BYTE *)malloc(len);
	    PtoByte(msg,C1);
	    F12toByte(&msg[64],w);
	    memcpy(&msg[448],id,idLen);
		K_ = (BYTE *)malloc(klen/8);
	    KDF(K_, msg, len, klen);  // Note: this step should also check if K is all zeros
	    K1_ = (BYTE *)malloc(mlen);
		memcpy(K1_,K_,mlen);
	    K2_ = (BYTE *)malloc(K2_len);
		memcpy(K2_,&K_[mlen],K2_len);

		M_ = (BYTE *)malloc(mlen);
		Bytes_XOR(M_, K1_, C2,mlen);
		u = (BYTE *)malloc(32);
		MAC(u, C2,mlen,K2_,K2_len);


	}else                    // Block mode decryption
	{
		Pairing_opt(&w,deB,C1);
        len = 64 + 384 + idLen;
	    msg = (BYTE *)malloc(len);
	    PtoByte(msg,C1);
	    F12toByte(&msg[64],w);
	    memcpy(&msg[448],id,idLen);
		K_ = (BYTE *)malloc(klen/8);
	    KDF(K_, msg, len, klen);  // Note: this step should also check if K is all zeros
	    K1_ = (BYTE *)malloc(K1_len);
		memcpy(K1_,K_,K1_len);
	    K2_ = (BYTE *)malloc(K2_len);
		memcpy(K2_,&K_[K1_len],K2_len);
		M_ = (BYTE *)malloc(32);
		// sm4 decryption
	    sm4_setkey_dec(&ctx,K1_);
	    sm4_crypt_ecb(&ctx,0,32,C2,M_);
		u = (BYTE *)malloc(32);
		MAC(u, C2,32,K2_,K2_len);
		m = (BYTE *)malloc(mlen);
		memcpy(m,M_,mlen);         // Remove padding to get actual message
	}
	finish = clock();
	time3 = (double)(finish-start);


	printf("\n********************************************\n");
	printf("*********SM9 Public Key Encryption Demo*********** \n");
	printf("********************************************\n");
	printf("***************************************\n");
	printf("****1. System master key and user key generation****\n");
	printf("***************************************\n");
	printf("Generator P1 in G1 = \n");
	P_toString(P1,HEX);
	printf("Generator P2 in G2 = \n");
	P2_toString(P2,HEX);
	printf("KGC private key ke = %s\n",Put(ke,HEX));
	printf("KGC public key P_pub_s = [ke]P1 = \n");
	P_toString(P_pub_e,HEX);
	printf("Entity B identifier IDB: %s\n",id);
	printf("Entity B private key deB = \n");
	P2_toString(deB,HEX);
	printf("Message to encrypt: %s",M);

	printf("\n************************************\n");
	printf("**************2. Encryption phase*******\n");
	printf("************************************\n");
	if(mode==0)
	{
		printf("******** Stream mode encryption *******\n");
		printf("K = \n");
	    printByte(K,klen/8);
		printf("\nK1 = \n");
	    printByte(K1,mlen);
		printf("\nK2 = \n");
	    printByte(K2,K2_len);
		printf("\nC = C1||C2||C3:\n");
		printf("C1 = [r]QB: \n");
		P_toString(C1,HEX);
		printf("C2 = M XOR K1:\n");
	    printByte(C2,mlen);
		printf("\nC3 = MAC(K2,C2):\n");
	    printByte(C3,32);

	}else
	{
		printf("******** Block mode encryption *******\n");
		printf("K = \n");
	    printByte(K,klen/8);
		printf("\nK1 = \n");
	    printByte(K1,K1_len);
		printf("\nK2 = \n");
	    printByte(K2,K2_len);
		printf("\nC = C1||C2||C3:\n");
		printf("C1 = [r]QB: \n");
		P_toString(C1,HEX);
		printf("M padded to: ");
	    printByte(input,32);
		printf("\nC2 = Enc(K1,M):\n");
	    printByte(C2,32);
		printf("\nC3 = MAC(K2,C2):\n");
	    printByte(C3,32);

	}

	printf("\n************************************\n");
	printf("**************3. Decryption phase*****\n");
	printf("************************************\n");
	if(mode==0)
	{
		printf("******** Stream mode decryption *******\n");
		printf("w_ = e(C1,deB): \n");
	    F12_toString(w,HEX);
		printf("K_ = KDF(C1||w_||IDB,klen): \n");
	    printByte(K_,klen/8);
		printf("\nK1_ = \n");
	    printByte(K1_,mlen);
		printf("\nK2_ = \n");
	    printByte(K2_,K2_len);

		printf("\nDecrypted M_ = C2 XOR K1_ :\n");
	    printByte(M_,mlen);
		printf("\nu = MAC(K2_,C2):\n");
	    printByte(u,32);
		if(Bytes_Equal(u,C3,32))
		   printf("\nu = C3, authentication successful\n");
		else
		{
		   printf("\nu != C3, authentication failed\n");
		   exit(0);
		}
		printf("\nDecrypted message M_: %s\n",M_);
	}else
	{
		printf("******** Block mode decryption *******\n");
		printf("w_ = e(C1,deB): \n");
	    F12_toString(w,HEX);
		printf("K_ = KDF(C1||w_||IDB,klen): \n");
	    printByte(K_,klen/8);
		printf("\nK1_ = \n");
	    printByte(K1_,K1_len);
		printf("\nK2_ = \n");
	    printByte(K2_,K2_len);

	     printf("\nDecrypted M_ = Dec(K1_,C2):\n");
	    printByte(M_,32);
		printf("\nu = MAC(K2_,C2):\n");
	    printByte(u,32);
		if(Bytes_Equal(u,C3,32))
		   printf("\nu = C3, authentication successful\n");
		else
		{
		   printf("\nu != C3, authentication failed\n");
		   exit(0);
		}
		printf("\nDecrypted message M_: %s\n",m);

		free(m);
	}

	printf("\nSM9 master key and user key generation time: %f ms\n",time1);
	printf("SM9 encryption time: %f ms\n",time2);
	printf("SM9 decryption time: %f ms\n",time3);

	free(K);
	free(K1);
	free(K2);
	free(C2);
	free(C3);
	free(msg);
	free(K_);
	free(K1_);
	free(K2_);
	free(M_);
	free(u);

}


/*
Key decapsulation algorithm:
K: Decapsulated key
klen: Length of K in bytes
*/
void PKC_kom(BYTE *K, BNPoint C,BNPoint2 deB,BYTE *ID,unsigned int klen)
{
	BNField12 w;
	BYTE *msg;
	unsigned int len1,len2;
	if(!P_isOnBNCurve(C))
	{
		printf("C in decapsulation is not in G1\n");
		exit(0);
	}
	Pairing_opt(&w,deB,C);
	len1 = strlen((const char*)ID);
	len2 = len1 + 64 + 384;

	msg = (BYTE*)malloc(len2);
	PtoByte(msg,C);
	F12toByte(&msg[64],w);
	memcpy(&msg[448],ID,len1);
    KDF(K, msg, len2, klen);  // Note: this step should also check if K is all zeros
	free(msg);
}


/*
Key encapsulation algorithm:
K: Encapsulated key
C: Encapsulated ciphertext
*/
void PKC_kem(BYTE *K,BNPoint *C,BYTE *ID,BNPoint P1,BNPoint2 P2,BNPoint P_pub_e,unsigned int klen)
{
	BYTE *msg,hid,*msg2;
	BNPoint QB;
	int len,len2;
	CBigInt r,h;
	BNField12 g,w;

	hid = 0x03;
	Get(&r,"AAC0541779C8FC45E3E2CB25C12B5D2576B2129AE8BB5EE2CBE5EC9E785C",HEX);
	len = strlen((const char*)ID);
	len += 1;
	msg = (BYTE*)malloc(len);
	memcpy(msg,ID,len-1);
	msg[len-1] = hid;
	Hash_1(&h, msg, len, BN.n);
	P_multiply(&QB,P1,h);
	P_add(&QB,QB,P_pub_e);
	P_multiply(C,QB,r);
	P_normorlize(C,*C);
	Pairing_opt(&g,P2,P_pub_e);
	F12_exp(&w,g,r);
	len2 = 64 + 384 + len - 1;
	msg2 = (BYTE *)malloc(len2);
	PtoByte(msg2,*C);
	F12toByte(&msg2[64],w);
	memcpy(&msg2[448],ID,len-1);
	KDF(K, msg2, len2, klen);  // Note: this step should also check if K is all zeros
	free(msg);
	free(msg2);
}



/*
   deB: Generated private key
   ke: Master private key
   ID: User ID string
   P2: Generator of group G2
*/
void PKC_Keygen(BNPoint2 *deB,CBigInt ke, BYTE *ID,BNPoint2 P2)
{
	int len;
	BYTE *msg;
	BYTE hid = 0x03;
	CBigInt t1,t2;
	len = strlen((const char*)ID);
	len +=1;
	msg = (BYTE*)malloc(len);
	memcpy(msg,ID,len-1);
	msg[len-1] = hid;
	Hash_1(&t1, msg, len, BN.n);
	Add_Big_Big(&t1,t1,ke);
	while(Cmp(t1,BN.ZERO)==0)
	{
		Hash_1(&t1, msg, len, BN.n);
	    Add_Big_Big(&t1,t1,ke);
	}
	Inv(&t2,t1,BN.n);
	Mul_Big_Big(&t2,t2,ke);
	if(Cmp(t2,BN.n)>=0)
		Mod_Big_Big(&t2,t2,BN.n);
	P2_multiply(deB,P2,t2);
	free(msg);
}



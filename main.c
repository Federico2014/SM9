//#include <stdio.h>
//#include "BigInt.h"
//#include "Params.h"
//#include "BNPoint2.h"
//#include "BNPairing.h"
//#include "utility.h"
//#include "SM9DSA.h"
//#include "SM9KA.h"
#include "SM9PKC.h"

//#include <time.h>

void test_BNField2();
void test_BNField4();
void test_BNField12();
void test_BNPoint();
void test_BNPoint2();
void test_Paiiring();
void test_Paiiring_Rate();
void test_Hash1();
void test_Hash2();
void test_SM4();
void main()
{

//	printf("×¢£º´Ó×óµ½ÓÒ·Ö±ðÎª´Ó¸ßÎ»µ½µÍÎ»£¡\n");
	SM9Params_init(&BN);
/*	printf("BN.t = %s\n",Put(BN.t,DEC));
	printf("BN.q = %s\n",Put(BN.q,DEC));
	printf("BN.trace = %s\n",Put(BN.tr,DEC));
	printf("BN.n = %s\n",Put(BN.n,DEC));
	printf("BN.ord = %s\n",Put(BN.ord,DEC));
	*/
	//test_BNField2();
	//test_BNField4();
	//test_BNField12();
	//test_BNPoint();
	//test_BNPoint2();
	//test_Paiiring();
	//test_Paiiring_Rate();
    // test_Hash1();
	// test_Hash2();
	//test_SM4();
	// DSA_Demo();
	//  KA_Demo();
	//   KEM_demo();
	  PKC_demo(1); //²ÎÊý0±íÊ¾SM9±íÊ¾ÐòÁÐ¼ÓÃÜÄ£Ê½£¬1¼°ÆäËü±íÊ¾²ÉÓÃ·Ö×é¼ÓÃÜÄ£Ê½
	 system("pause");
	
}

void test_SM4()
{
	unsigned char key[16] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	unsigned char input[16] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	unsigned char output[16];
	BYTE key2[16];
	BYTE input2[32];
	BYTE output2[32];
	BYTE *str1 = (BYTE*)"58373260F067EC48667C21C144F8BC33";
	BYTE *str2 = (BYTE*)"4368696E65736520494245207374616E646172640C0C0C0C0C0C0C0C0C0C0C0C";
//    BYTE *str2 = (BYTE*)"4368696E65736520494245207374616E64617264";
	//BYTE *str3 = (BYTE*)"";
	sm4_context ctx;
	unsigned long i;

	//encrypt standard testing vector
	sm4_setkey_enc(&ctx,key);
	sm4_crypt_ecb(&ctx,1,16,input,output);
	for(i=0;i<16;i++)
		printf("%02x ", output[i]);
	printf("\n");

	//decrypt testing
	sm4_setkey_dec(&ctx,key);
	sm4_crypt_ecb(&ctx,0,16,output,output);
	for(i=0;i<16;i++)
		printf("%02x ", output[i]);
	printf("\n");
/*
	//encrypt 1M times testing vector based on standards.
	i = 0;
	sm4_setkey_enc(&ctx,key);
	while (i<1000000) 
    {
		sm4_crypt_ecb(&ctx,1,16,input,input);
		i++;
    }
	for(i=0;i<16;i++)
		printf("%02x ", input[i]);
	printf("\n");
*/
    //SM9 encrypt testing vector
	Hex2Byte(key2, str1, 32);
	Hex2Byte(input2, str2, 64);
	//¼ÓÃÜ
	sm4_setkey_enc(&ctx,key2);
	sm4_crypt_ecb(&ctx,1,32,input2,output2);
	for(i=0;i<32;i++)
		printf("%02x ", output2[i]);
	printf("\n");
	//½âÃÜ
	sm4_setkey_dec(&ctx,key2);
	sm4_crypt_ecb(&ctx,0,32,output2,output2);
	for(i=0;i<32;i++)
		printf("%02x ", output2[i]);
	printf("\n");

	system("pause");
    
}

void test_Hash2()
{
	CBigInt h1;
	unsigned int  len;
	BYTE hex1[81]= "4368696E65736520494253207374616E6461726481377B8FDBC2839B4FA2D0E0F8AA6853BBBE9E9C";
	BYTE hex2[81]= "4099608F8612C6078ACD7563815AEBA217AD502DA0F48704CC73CABB3C06209BD87142E14CBD99E8";
	BYTE hex3[81]= "BCA1680F30DADC5CD9E207AEE32209F6C3CA3EC0D800A1A42D33C73153DED47C70A39D2E8EAF5D17";
	BYTE hex4[81]= "9A1836B359A9D1D9BFC19F2EFCDB829328620962BD3FDF15F2567F58A543D25609AE943920679194";
	BYTE hex5[81]= "ED30328BB33FD15660BDE485C6B79A7B32B013983F012DB04BA59FE88DB889321CC2373D4C0C35E8";
	BYTE hex6[81]= "4F7AB1FF33679BCA575D67654F8624EB435B838CCA77B2D0347E65D5E46964412A096F4150D8C5ED";
	BYTE hex7[81]= "E5440DDF0656FCB663D24731E80292188A2471B8B68AA993899268499D23C89755A1A89744643CEA";
	BYTE hex8[81]= "D40F0965F28E1CD2895C3D118E4F65C9A0E3E741B6DD52C0EE2D25F5898D60848026B7EFB8FCC1B2";
	BYTE hex9[81]= "442ECF0795F8A81CEE99A6248F294C82C90D26BD6A814AAF475F128AEF43A128E37F80154AE6CB92";
	BYTE hex10[81]= "CAD7D1501BAE30F750B3A9BD1F96B08E97997363911314705BFB9A9DBB97F75553EC90FBB2DDAE53";
	BYTE hex11[9] = "C8F68E42";
	BYTE msg[405];

	
    printf("Hash1 test: begin!\n");
    Hex2Byte(msg, hex1, 80);
	Hex2Byte(&msg[40], hex2, 80);
    Hex2Byte(&msg[80], hex3, 80);
	Hex2Byte(&msg[120], hex4, 80);
    Hex2Byte(&msg[160], hex5, 80);
	Hex2Byte(&msg[200], hex6, 80);
    Hex2Byte(&msg[240], hex7, 80);
	Hex2Byte(&msg[280], hex8, 80);
    Hex2Byte(&msg[320], hex9, 80);
	Hex2Byte(&msg[360], hex10, 80);
	Hex2Byte(&msg[400], hex11, 8);

	Hash_2(&h1, msg, 404, BN.n);
	printf("h2 = %s\n",Put(h1,HEX));
	//823C4B21E4BD2DFE1ED92C606653E996668563152FC33F55D7BFBB9BD9705ADB
	printf("Hash1 test: end!\n");
}



void test_Hash1()
{
	CBigInt h1;
	unsigned int  len;
	BYTE msg[6]="Alice";
	msg[5] = 0x01;
    printf("Hash1 test: begin!\n");

	Hash_1(&h1, msg, 6, BN.n);
	printf("h1 = %s\n",Put(h1,HEX));
	 //2ACC468C 3926B0BD B2767E99 FF26E084 DE9CED8D BC7D5FBF 418027B6 67862FAB
	printf("Hash1 test: end!\n");
}



void test_Paiiring_Rate()
  {
	CBigInt a,b,c,d,e,f,zero,ks,kt;
	BNField2 b1,b2;
	BNPoint2 Q,Q1,Q3,Q4,Q5;
	BNPoint P,P1,P2;
	BNField12 g,f1,f2,f3,f4,f5;
    clock_t start,finish;
	int i,n;
	double time;
	
	Get(&a,"93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD",HEX);
	Get(&b,"21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616",HEX);
	Get(&c,"85AEF3D078640C98597B6027B441A01FF1DD2C190F5E93C454806C11D8806141",HEX);
	Get(&d,"3722755292130B08D2AAB97FD34EC120EE265948D19C17ABF9B7213BAF82D65B",HEX);
	Get(&e,"17509B092E845C1266BA0D262CBEE6ED0736A96FA347C8BD856DC76B84EBEB96",HEX);
	Get(&f,"A7CF28D519BE3DA65F3170153D278FF247EFBA98A71A08116215BBA5C999A7C7",HEX);

    printf("BNPairing Rate test: begin!\n");

	P_construct_xy(&P,a,b);

	F2_construct(&b1,d,c);
	F2_construct(&b2,f,e);    
    P2_construct_xy(&Q,b1,b2);
  
	Pairing_Rate(&g,Q,P);
    
    P_twice(&P1,P);
	P_normorlize(&P1,P1);
	Pairing_Rate(&f1,Q,P1);

	P2_twice(&Q1,Q);
	Pairing_Rate(&f2,Q1,P);

	F12_square(&f3,g);

	if(F12_equal(f1,f2))
		printf("Rate Paring right 1!\n");
	if(F12_equal(f2,f3))
		printf("Rate Paring right 2!\n"); 
/*	printf("f1 = \n");
	F12_toString(f1,DEC);
	printf("f2 = \n");
	F12_toString(f2,DEC);
	printf("f3 = \n");
	F12_toString(f3,DEC);
 */  // printf("BNPairing test: over!\n");
	
/*	
	printf("SM9Ë«ÏßÐÔ¶ÔRate¼ÆËã£º\n");
	printf("P = \n");
	P_toString_d(P);
	printf("Q = \n");
	P2_toString_d(Q); 
	printf("SM9_Rate(Q,P) = \n");
	F12_toString_d(g);
//	printf("SM9_opt(Q,P) = \n");
//	Pairing_opt(&g,Q,P);
//	F12_toString_d(g);

	printf("SM9_Rate(Q,2P) = \n");
	F12_toString_d(f1);
	printf("SM9_Rate(2Q,P) = \n");
	F12_toString_d(f2);
	printf("SM9_Rate(Q,P)^2 = \n");
	F12_toString_d(f3);
	printf("SM9_Rate(Q,2P) = SM9_Rate(2Q,P) = SM9_Rate(Q,P)^2 \n");
*/
   printf("²âÊÔ¿ªÊ¼£º\n");
   //  Pairing_opt(&g,Q,P);
       n = 10;
	   start = clock();
	   for(i = 0; i<n; i++)
     	Pairing_Rate(&g,Q,P);
	   finish = clock();
      time = (double)(finish-start)/n;
      printf("SM9 Pairing time cost£º%f ms\n",time);
/*
       mpz_init_set_str(ks,"0130E78459D78545CB54C587E02CF480CE0B66340F319F348A1D5B1F2DC5F4",16);
       P2_multiply(&Q3,Q,ks);
	// P2_normorlize(&Q1,Q1);
       Pairing_Rate(&g,Q3,P);
	   printf("P = \n");
	   P_toString_H(P);
       printf("Q = \n");
	   P2_toString_H(Q);
       printf("ks = %s\n",mpz_get_str(NULL, 16, ks));
       printf("SM9_Opt(ks*Q,P) = \n"); 	   
	   F12_toString_H(g);

       mpz_init_set_str(ks,"0130E78459D78545CB54C587E02CF480CE0B66340F319F348A1D5B1F2DC5F4",16);
       Pairing_Rate(&g,Q,P);
	
       P_multiply(&P1,P,ks);
       P_normorlize(&P1,P1);
       Pairing_Rate(&f1,Q,P1);

       P2_multiply(&Q4,Q,ks);
	   Pairing_Rate(&f2,Q4,P);

	   F12_exp(&f3,g,ks);
	 //  P2_toString_d(Q4);
       printf("ks ²âÊÔ\n");  
	   if(F12_equal(f1,f2))
		  printf("Paring right 1!\n");
	   if(F12_equal(f2,f3))
	      printf("Paring right 2!\n");  
   
	   
       F12_toString_H(f1);
	   printf("\n");  
       F12_toString_H(f2);
	   printf("\n"); 
       F12_toString_H(f3); 

	   P_multiply(&P2,P1,BN.n);
	   P_normorlize(&P2,P2);
	   P_toString_d(P2);
	   printf("Q = \n"); 
	   P2_toString_d(Q);
	   printf("Q4 = \n"); 
	   P2_toString_d(Q4);
	   P2_multiply(&Q5,Q4,BN.n);
	   P2_normorlize(&Q5,Q5);
	   P2_toString_d(Q5);
	   F12_exp(&f3,f3,BN.n);
	   F12_toString_d(f3);
   */	
 /*
	   //²âÊÔ R(kt*Q,ks*P) = R(Q,P)^(kt*ks)
       mpz_init_set_str(ks,"0130E78459D78545CB54C587E02CF480CE0B66340F319F348A1D5B1F2DC5F4",16);
       mpz_init_set_str(kt,"5730E78459D78545CB54C587E02CF480CE0B66340F319F348A1D5B1F2D4571",16);
 //      mpz_init_set_str(ks,"4",16);
 //      mpz_init_set_str(kt,"3",16);
       Pairing_Rate(&g,Q,P);
	
       P_multiply(&P1,P,ks);
       P_normorlize(&P1,P1);
       Pairing_Rate(&f1,Q,P1);
    	if(P_isOnBNCurve(P1))
		{
           printf("BNPoint test:¡¡p1 is  on the Curve \n");
		}       
       P2_multiply(&Q4,Q,kt);
	   if(P2_isOnBNTCurve(Q4))
	   {
          printf("BNPoint2 test:¡¡p2 is on the BNT Curve \n");
	   } 
        printf(" ²âÊÔ¿ªÊ¼\n");
		P_toString_d(P1);
		P2_toString_d(Q4);
	    Pairing_Rate(&f5,Q4,P1);
    //    mpz_mul(kt,kt,ks);
	   F12_exp(&f4,g,ks);
	   F12_exp(&f4,f4,kt);
   
	  
	   if(F12_equal(f4,f5))
	      printf("R(kt*Q,ks*P) == R(Q,P)^(kt*ks)\n");  
	   printf(" f4 = \n");
	   F12_toString_d(f4);
	   printf(" f5 = \n");
	   F12_toString_d(f5);
   */     
	  printf("BNPairing test: over!\n");	
 
 
  }


void test_Paiiring()
  {
	CBigInt a,b,c,d,e,f,zero,ks,kt;
	BNField2 b1,b2;
	BNPoint2 Q,Q1,Q3,Q4,Q5;
	BNPoint P,P1,P2;
	BNField12 g,f1,f2,f3,f4,f5;
    clock_t start,finish;
	int i,n;
	double time;
   // mpz_init(ks);

	Get(&a,"93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD",HEX);
	Get(&b,"21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616",HEX);
	Get(&c,"85AEF3D078640C98597B6027B441A01FF1DD2C190F5E93C454806C11D8806141",HEX);
	Get(&d,"3722755292130B08D2AAB97FD34EC120EE265948D19C17ABF9B7213BAF82D65B",HEX);
	Get(&e,"17509B092E845C1266BA0D262CBEE6ED0736A96FA347C8BD856DC76B84EBEB96",HEX);
	Get(&f,"A7CF28D519BE3DA65F3170153D278FF247EFBA98A71A08116215BBA5C999A7C7",HEX);




    printf("BNPairing test: begin!\n");

    P_construct_xy(&P,a,b);

	F2_construct(&b1,d,c);
	F2_construct(&b2,f,e);    
    P2_construct_xy(&Q,b1,b2);
 
	Pairing_opt(&g,Q,P);
    //F12_toString_d(g,DEC);
	P_twice(&P1,P);
	P_normorlize(&P1,P1);
	Pairing_opt(&f1,Q,P1);

	P2_twice(&Q1,Q);
	Pairing_opt(&f2,Q1,P);

	F12_square(&f3,g);

	if(F12_equal(f1,f2))
		printf("Paring right 1!\n");
	if(F12_equal(f2,f3))
		printf("Paring right 2!\n");  
    printf("BNPairing test: over!\n");
	
	printf("SM9Ë«ÏßÐÔ¶Ô¼ÆËã£º\n");
  /* 	printf("P = \n");
	P_toString(P,DEC);
	printf("Q = \n");
	P2_toString_d(Q,DEC);
	printf("SM9_Opt(Q,P) = \n");
    F12_toString_d(g,DEC);
	printf("SM9_Opt(Q,2P) = \n");
    F12_toString_d(f1,DEC);
	printf("SM9_Opt(2Q,P) = \n");
    F12_toString_d(f2,DEC);
	printf("SM9_Opt(Q,P)^2 = \n");
    F12_toString_d(f3,DEC);
	*/
	//printf("SM9_Opt(Q,2P) = SM9_Opt(2Q,P) = SM9_Opt(Q,P)^2 \n");

    printf("²âÊÔ¿ªÊ¼£º\n");
   //  Pairing_opt(&g,Q,P);
       n = 10;
	   start = clock();
	   for(i = 0; i<n; i++)
	     Pairing_opt(&g,Q,P);
	   finish = clock();
      time = (double)(finish-start)/n;
      printf("SM9 Pairing time cost£º%f ms\n",time);

	  Get(&ks,"0130E78459D78545CB54C587E02CF480CE0B66340F319F348A1D5B1F2DC5F4",HEX);
   
       P2_multiply(&Q3,Q,ks);
	// P2_normorlize(&Q1,Q1);
       Pairing_opt(&g,Q3,P);
	    printf("P = \n");
	   P_toString(P,HEX);
	   printf("Q = \n");
	   P2_toString(Q,HEX);
	   printf("SM9_Opt(Q,P) = \n");
       printf("ks = %s\n",Put(ks,HEX));
       printf("SM9_Opt(ks*Q,P) = \n"); 	   
       F12_toString(g,HEX);
/*
       Get(&ks,"0130E78459D78545CB54C587E02CF480CE0B66340F319F348A1D5B1F2DC5F4",HEX);
       g = Pairing_opt(Q,P);
	
       P1 = P_multiply(P,ks);
       P1 = P_normorlize(P1);
       f1 = Pairing_opt(Q,P1);

       Q4 = P2_multiply(Q,ks);
	   f2 = Pairing_opt(Q4,P);

	   f3 = F12_exp(g,ks);
       printf("ks ²âÊÔ\n");  
	   if(F12_equal(f1,f2))
		  printf("Paring right 1!\n");
	   if(F12_equal(f2,f3))
	      printf("Paring right 2!\n");  
      
	   
       F12_toString(f1,HEX);
	   printf("\n");  
       F12_toString(f2,HEX);
	   printf("\n"); 
       F12_toString(f3,HEX); 

	   P2 = P_multiply(P1,BN.n);
	   P2 = P_normorlize(P2);
	   P_toString(P2,DEC);
       printf("Q = \n"); 
	   P2_toString(Q,DEC);
       printf("Q4 = \n"); 
	   P2_toString(Q4,DEC);
	   Q5 = P2_multiply(Q4,BN.n);
	   Q5 = P2_normorlize(Q5);
	   P2_toString(Q5,DEC);
	   f3 = F12_exp(f3,BN.n);
	   F12_toString(f3,DEC);
	
	   //²âÊÔ R(kt*Q,ks*P) = R(Q,P)^(kt*ks)
       ks = Get("0130E78459D78545CB54C587E02CF480CE0B66340F319F348A1D5B1F2DC5F4",16);
       kt = Get("5730E78459D78545CB54C587E02CF480CE0B66340F319F348A1D5B1F2D4571",16);
 //      mpz_init_set_str(ks,"4",16);
 //      mpz_init_set_str(kt,"3",16);
       g = Pairing_opt(Q,P);
	
       P1 = P_multiply(P,ks);
       P1 = P_normorlize(P1);
    // Pairing_opt(&f1,Q,P1);
    	if(P_isOnBNCurve(P1))
		{
           printf("BNPoint test:¡¡p1 is  on the Curve \n");
		}       
       Q4 = P2_multiply(Q,kt);
	   if(P2_isOnBNTCurve(Q4))
	   {
          printf("BNPoint2 test:¡¡p2 is on the BNT Curve \n");
	   } 
        printf(" ²âÊÔ¿ªÊ¼\n");
		P_toString(P1,DEC);
		P2_toString(Q4,DEC);
	    f5 = Pairing_opt(Q4,P1);
    //    mpz_mul(kt,kt,ks);
	   f4 = F12_exp(g,ks);
	   f4 = F12_exp(f4,kt);
     
	  
	   if(!F12_equal(f4,f5))
	      printf("R(kt*Q,ks*P) != R(Q,P)^(kt*ks)\n");  
	   printf(" f4 = \n");
	   F12_toString(f4,DEC);
	   printf(" f5 = \n");
	   F12_toString(f5,DEC);
       
	  printf("BNPairing test: over!\n");	
/*
  */
  }


  void test_BNPoint2()
{
	CBigInt a,b,c,d,e,f,neg_1;
	BNField2 b1,b2,b3,t1,t2,t3;
    BNPoint2 p1,p2,p3,p4,p5,p6;
		
	Get(&a,"93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD",HEX);
	Get(&b,"21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616",HEX);
	Get(&c,"85AEF3D078640C98597B6027B441A01FF1DD2C190F5E93C454806C11D8806141",HEX);
	Get(&d,"3722755292130B08D2AAB97FD34EC120EE265948D19C17ABF9B7213BAF82D65B",HEX);
	Get(&e,"17509B092E845C1266BA0D262CBEE6ED0736A96FA347C8BD856DC76B84EBEB96",HEX);
	Get(&f,"A7CF28D519BE3DA65F3170153D278FF247EFBA98A71A08116215BBA5C999A7C7",HEX);
	
    printf("BNPoint2 test: begin!\n");
   
	    
	F2_construct(&b1,d,c);
	F2_construct(&b2,f,e);
    
    P2_construct_xy(&p1,b1,b2);
//	P2_toString_d(p1);
	//²âÊÔp1ÊÇ·ñÔÚBNÅ¤ÇúÏßÉÏ
	if(!P2_isOnBNTCurve(p1))
	{
        printf("BNPoint2 test:¡¡p is not on the Curve \n");
	}else printf("Test 1 passed!\n");
	
	//²âÊÔn*p1ÊÇ·ñÎªÁã
//	printf("²âÊÔ¿ªÊ¼£º\n");
	P2_multiply(&p2,p1,BN.n);
	if(!P2_isZero(p2))
	{
        printf("BNPoint2 test:¡¡n*p != 0 \n");
	}else printf("Test 2 passed!\n");

	//²âÊÔ -(-p1) == p1
	P2_negate(&p4,p1);
	P2_negate(&p4,p4);
	if(!P2_equal(p1,p4))
	{
        printf("BNPoint2 test:¡¡ -(-p1) != p1 \n");
	}else printf("Test 3 passed!\n");


//	printf("\n");
    
	//²âÊÔ p1+p2 = p2+p1
	P2_add(&p4,p1,p2);
	P2_add(&p5,p2,p1);
	if(!P2_equal(p4,p5))
	{
        printf("BNPoint2 test:¡¡p1+p2 != p2+p1 \n");
	}else printf("Test 4 passed!\n");


	//²âÊÔ p1+p1 = 2*p1
	P2_add(&p4,p1,p1);
	P2_twice(&p5,p1);
	if(!P2_equal(p4,p5))
	{
        printf("BNPoint2 test:¡¡p1+p1 != 2*p1 \n");
	}else printf("Test 5 passed!\n");

	//²âÊÔ 2p1+2p1 == p1+3p1
	
	P2_twice(&p3,p1);
	P2_twice(&p4,p3);

   	P2_add(&p5,p3,p1);
 	P2_add(&p5,p1,p5);	
	if(!P2_equal(p4,p5))
	{
        printf("BNPoint2 test:¡¡ 2p1+2p1 != p1+3p1 \n");
	}else printf("Test 6 passed!\n");


   
 	//²âÊÔ p+0 == p
	P2_multiply(&p4,p1,BN.n);
	P2_add(&p5,p1,p4);
	if(!P2_equal(p1,p5))
	{
        printf("BNPoint2 test:¡¡p + 0 != p \n");
	}else printf("Test 7 passed!\n");
   
    //²âÊÔ 0*p == p
	P2_multiply(&p5,p1,BN.ZERO);
	if(!P2_isZero(p5))
	{
        printf("BNPoint test:¡¡ 0*p != 0 \n");
	}else printf("Test 8 passed!\n");
 
    //²âÊÔ (-m)*x == m*(-x)
	
	P2_multiply(&p3,p1,b);
	P2_negate(&p3,p3);
    P2_negate(&p2,p1);
	P2_multiply(&p5,p2,b);

	if(!P2_equal(p3,p5))
	{
        printf("BNPoint2 test:¡¡(-m)*x != m*(-x) \n");
	} else printf("Test 9 passed!\n");

    //²âÊÔ (m+n)*x == m*x+n*x
		
    Add_Big_Big(&c,a,b);
	P2_multiply(&p2,p1,c);
	P2_multiply(&p3,p1,a);
	P2_multiply(&p4,p1,b);
	P2_add(&p5,p3,p4);
	if(!P2_equal(p2,p5))
	{
        printf("BNPoint test:¡¡ (m+n)*x == m*x+n*x \n");
	}else printf("Test 10 passed!\n");
 	
    //²âÊÔ x*m*n == x*n*m
    P2_multiply(&p2,p1,c);
   	P2_multiply(&p2,p2,d);
   	P2_multiply(&p3,p1,d);
   	P2_multiply(&p3,p3,c); 
	if(!P2_equal(p2,p3))
	{
        printf("BNPoint test: (m*n)*x != m*(n*x) \n");
	}else printf("Test 11 passed!\n");
	

	//²âÊÔ p1+p2+p3 == p1+(p2+p3) 

   	P2_add(&p4,p1,p2);
	P2_add(&p4,p4,p3);

 	P2_add(&p5,p2,p3);
	P2_add(&p5,p1,p5);

	if(!P2_equal(p4,p5))
	{
       printf("BNPoint test:¡¡p1+p2+p3 != p1+(p2+p3)\n");
	}else printf("Test 12 passed!\n");

   //²âÊÔ p1+(-p1) = 0
	P2_twice(&p2,p1);
	P2_negate(&p4,p2);
   // P2_toString_d(p4);

	CBigInt_neg(&neg_1,BN.ONE);
    P2_multiply(&p3,p2,neg_1);
 //   P2_toString_d(p3);

	P2_add(&p5,p2,p4);
	//P2_normorlize(&p5,p5);
//    P2_toString_d(p5);

	if(!P2_isZero(p5))
	{
        printf("BNPoint2 test:¡¡p1+(-p1) != 0 \n");
	}else printf("Test 13 passed!\n");
	
	//²âÊÔ p1+(-p1) = 0
//	printf("²âÊÔ¿ªÊ¼£º\n");
    P2_construct_xy(&p1,b1,b2);
    P2_negate(&p2,p1);
	P2_add(&p2,p2,p1);
    if(!P2_isZero(p2))
	{
		printf("BNPoint2 Test:¡¡P+(-p) != 0\n");
	}else printf("Test 14 passed!\n");
	//	²âÊÔFrobenius
    P2_construct_xy(&p1,b1,b2);
    P2_multiply(&p2,p1,BN.q);
	P2_frobenius(&p3,p1);
    if(!P2_equal(p2,p3))
	{
		printf("inconsistent Frobenius\n");
	}else printf("Test 15 passed!\n");

	//	²âÊÔFrobenius 2
    //P2_construct_xy(&p1,b1,b2);
    P2_multiply(&p2,p1,BN.q);
	P2_multiply(&p2,p2,BN.q);
	P2_frobenius(&p3,p1);
	P2_frobenius(&p3,p3);
    if(!P2_equal(p2,p3))
	{
		printf("inconsistent Frobenius 2\n");
	}else printf("Test 16 passed!\n");

	//	²âÊÔFrobenius 3
    //P2_construct_xy(&p1,b1,b2);
    P2_multiply(&p2,p1,BN.q);
	P2_multiply(&p2,p2,BN.q);
	P2_multiply(&p2,p2,BN.q);
	P2_frobenius(&p3,p1);
	P2_frobenius(&p3,p3);
	P2_frobenius(&p3,p3);
    if(!P2_equal(p2,p3))
	{
		printf("inconsistent Frobenius 3\n");
	}else printf("Test 17 passed!\n");
 /*   
 */
	printf("BNPoint2 test: over!\n");
}

void test_BNPoint()
{
	CBigInt a,b,c,d,e,f;
	BNPoint p1,p2,p3,p4,p5;

	Get(&a,"93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD",HEX);
	Get(&b,"21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616",HEX);
	Get(&c,"85AEF3D078640C98597B6027B441A01FF1DD2C190F5E93C454806C11D8806141",HEX);
	Get(&d,"3722755292130B08D2AAB97FD34EC120EE265948D19C17ABF9B7213BAF82D65B",HEX);
	Get(&e,"17509B092E845C1266BA0D262CBEE6ED0736A96FA347C8BD856DC76B84EBEB96",HEX);
	Get(&f,"A7CF28D519BE3DA65F3170153D278FF247EFBA98A71A08116215BBA5C999A7C7",HEX);

    printf("BNPoint test: begin!\n");


    P_construct(&p1,a,b,c);
	P_construct(&p2,b,c,d);
	P_construct(&p3,c,d,f);

	//²âÊÔ p1+(-p1) = 0
	P_negate(&p4,p1);
	P_add(&p4,p1,p4);
	if(!P_isZero(p4))
	{
        printf("BNPoint test:¡¡p1+(-p1) != 0 \n");
	}else printf("Test 1 passed!\n");
//	P_toString_d(p4);
//	printf("\n");
  
	//²âÊÔ p1+p2 = p2+p1

	P_add(&p4,p1,p2);
	P_add(&p5,p2,p1);
	//p4 = P_normorlize(p4);
	//p5 = P_normorlize(p5);
	//P_toString(p4,10);
	//P_toString(p5,10);
	if(!P_equal(p4,p5))
	{
        printf("BNPoint test:¡¡p1+p2 != p2+p1 \n");
	}else printf("Test 2 passed!\n");

 
	//²âÊÔ p1+p1 = 2*p1
	
	P_add(&p4,p1,p1);

	P_twice(&p5,p1);

	if(!P_equal(p4,p5))
	{
        printf("BNPoint test:¡¡p1+p1 != 2*p1 \n");
	}else printf("Test 3 passed!\n");
 
	//²âÊÔ 2p1+2p1 == p1+3p1
	// P_toString(p1,10);
	P_twice(&p3,p1);
	P_twice(&p4,p3);

   	P_add(&p5,p3,p1);
 	P_add(&p5,p1,p5);

	// p3 = P_normorlize(p3);
	 // P_toString(p3,10);
	//P_toString(p5,10);

	if(!P_equal(p4,p5))
	{
        printf("BNPoint test:¡¡ 2p1+2p1 != p1+3p1 \n");
	}else printf("Test 4 passed!\n");


	//²âÊÔ n*p == 0
    P_construct_xy(&p1,a,b);

     if(!P_isOnBNCurve(p1))
	{
        printf("BNPoint test:¡¡P is not on the BN Curve!\n");
	} else printf("Test 5 passed!\n");

	P_multiply(&p2,p1,b);
	P_multiply(&p3,p1,c);

//	P_toString_d(p1);
	//P_toString(p1,DEC);
//	printf("BN.n = %s\n",Put(BN.n,DEC));
    P_multiply(&p4,p1,BN.n);
//	P_toString(p4,DEC);
    if(!P_isZero(p4))
	{
        printf("BNPoint test:¡¡n*P != 0 \n");
	} else printf("Test 6 passed!\n");
  
 	//²âÊÔ p+0 == p
	P_add(&p5,p2,p4);
	if(!P_equal(p2,p5))
	{
        printf("BNPoint test:¡¡p + 0 != p \n");
	} else printf("Test 7 passed!\n");
    //²âÊÔ -(-p) == p
	P_negate(&p5,p1);
	P_negate(&p5,p5);
	if(!P_equal(p1,p5))
	{
        printf("BNPoint test:¡¡ -(-p) != p \n");
	} else printf("Test 8 passed!\n");
    
    //²âÊÔ 0*p == 0
	P_multiply(&p5,p1,BN.ZERO);
	if(!P_isZero(p5))
	{
        printf("BNPoint test:¡¡ 0*p != 0 \n");
	}else printf("Test 9 passed!\n");

    //²âÊÔ (-m)*x == m*(-x)

	
	//c = CBigInt_neg(b);
	P_multiply(&p3,p1,b);
	P_negate(&p3,p3); 
    P_negate(&p2,p1);
	P_multiply(&p5,p2,b);

	if(!P_equal(p3,p5))
	{
        printf("BNPoint test:¡¡(-m)*x != m*(-x) \n");
	}else printf("Test 10 passed!\n");

    //²âÊÔ (m+n)*x == m*x+n*x

	Get(&a,"93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD",HEX);
	Get(&b,"21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616",HEX);
	Add_Big_Big(&c,a,b);
	P_multiply(&p2,p1,c);
	P_multiply(&p3,p1,a);
	P_multiply(&p4,p1,b);
	P_add(&p5,p3,p4);
	if(!P_equal(p2,p5))
	{
        printf("BNPoint test:¡¡ (m+n)*x == m*x+n*x \n");
	}else printf("Test 11 passed!\n");
 	
    //²âÊÔ x*m*n == x*n*m
	Get(&a,"93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD",HEX);
	Get(&b,"21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616",HEX);
	Get(&c,"85AEF3D078640C98597B6027B441A01FF1DD2C190F5E93C454806C11D8806141",HEX);
	Get(&d,"3722755292130B08D2AAB97FD34EC120EE265948D19C17ABF9B7213BAF82D65B",HEX);
	Get(&e,"17509B092E845C1266BA0D262CBEE6ED0736A96FA347C8BD856DC76B84EBEB96",HEX);
	Get(&f,"A7CF28D519BE3DA65F3170153D278FF247EFBA98A71A08116215BBA5C999A7C7",HEX);

	P_construct_xy(&p1,a,b);
	P_multiply(&p2,p1,c);
   	P_multiply(&p2,p2,d);
   	P_multiply(&p3,p1,d);
   	P_multiply(&p3,p3,c); 
	if(!P_equal(p2,p3))
	{
        printf("BNPoint test: (m*n)*x != m*(n*x) \n");
	}else printf("Test 12 passed!\n");
	

	//²âÊÔ p1+p2+p3 == p1+(p2+p3) 

   	P_add(&p4,p1,p2);
	P_add(&p4,p4,p3);

 	P_add(&p5,p2,p3);
	P_add(&p5,p1,p5);

	if(!P_equal(p4,p5))
	{
       printf("BNPoint test:¡¡p1+p2+p3 != p1+(p2+p3)\n");
	} else printf("Test 13 passed!\n");
/* */ 
	printf("BNPoint test: over!\n");
}


void test_BNField12()
{
	CBigInt a,b,c,d,e,f,zero;
//	mpz_t a1,b1,c1,d1,e1,f1;
	BNField2 b1,b2,b3,b4,b5,b6;
	BNField2 t1,t2,t3,t4,t5,t6;
	BNField4 B1,B2,B3,T1,T2,T3;
	BNField12 BN1,BN2,BN3,TN1,TN2,TN3;
	
	  
	Get(&a,"93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD",HEX);
	Get(&b,"21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616",HEX);
	Get(&c,"85AEF3D078640C98597B6027B441A01FF1DD2C190F5E93C454806C11D8806141",HEX);
	Get(&d,"3722755292130B08D2AAB97FD34EC120EE265948D19C17ABF9B7213BAF82D65B",HEX);
	Get(&e,"17509B092E845C1266BA0D262CBEE6ED0736A96FA347C8BD856DC76B84EBEB96",HEX);
	Get(&f,"A7CF28D519BE3DA65F3170153D278FF247EFBA98A71A08116215BBA5C999A7C7",HEX);
	
	printf("BNField12 test: Begin! \n");

    F2_construct(&b1,a,b);
    F2_construct(&b2,a,c);
	F2_construct(&b3,a,d);
    F2_construct(&t1,a,b);
    F2_construct(&t2,b,d);
	F2_construct(&t3,b,f);

    F4_construct(&B1,b1,t1);
    F4_construct(&B2,b2,t2);
	F4_construct(&B3,b3,t3);

    F12_construct(&BN1,B1,B2,B3);
	F12_construct(&BN2,B2,B3,B1);
	F12_construct(&BN3,B3,B1,B2);


	//F12_toString(BN1,HEX);

	F12_multiply_I(&TN1,BN1,BN.ZERO);

	//F12_toString(TN1,HEX);
	if(!F12_isZero(TN1))
	{
		printf("BNField12 test: B1*0 != 0 \n");

	}else printf("Test 1 passed!\n");



	F12_add(&TN1,BN1,BN2);  
    F12_add(&TN2,BN2,BN1);

	if(!F12_equal(TN1,TN2))
	{
		printf("BNField12 test: BN1+BN2 != BN2+BN1 \n");

	}else printf("Test 2 passed!\n");

	F12_add(&TN1,BN1,BN2);
	F12_add(&TN1,TN1,BN3);
    F12_add(&TN2,BN2,BN3);
    F12_add(&TN2,TN2,BN1);

	if(!F12_equal(TN1,TN2))
	{
		printf("BNField12 test: (B1+B2)+B3 != B1+(B2+B3) \n");

	}else printf("Test 3 passed!\n");

    F12_add(&TN1,BN1,BN2);
	F12_add_F4(&TN1,TN1,B1);
    F12_add_F4(&TN2,BN2,B1);
    F12_add(&TN2,BN1,TN2);	
	if(!F12_equal(TN1,TN2))
	{
		printf("BNField12 test: (BN1+BN2)+k != BN1+(BN2+k) \n");
	}else printf("Test 4 passed!\n");

    // ²âÊÔb1 - b2 == -(b2 - b1) 
    F12_substract(&TN1,BN1,BN2);
    F12_substract(&TN2,BN2,BN1);
	F12_negate(&TN2,TN2);
	if(!F12_equal(TN1,TN2))
	{
		printf("BNField12 test: BN1 - BN2 != -(BN2 - BN1) \n");
	}else printf("Test 5 passed!\n");

   // ²âÊÔ b1 - b1 == 0
    F12_substract(&TN1,BN1,BN1);
	if(!F12_isZero(TN1))
	{
		printf("BNField12 test: BN1 - BN1 != 0 \n");
	}else printf("Test 6 passed!\n");
 
    // ²âÊÔ b1 * 2  != b1 + b1
    F12_add(&TN1,BN1,BN1);  
	F12_multiply_i(&TN2,BN1,2);
	if(!F12_equal(TN1,TN2))
	{
		printf("BNField12 test: BN1 * 2  != BN1 + BN1 \n");
	}else printf("Test 7 passed!\n");

    
   // ²âÊÔ b1 * b2 == b2*b1

	F12_multiply(&TN1,BN1,BN2);
	F12_multiply(&TN2,BN2,BN1);

	if(!F12_equal(TN1,TN2))
	{
		printf("BNField12 test: BN1 * BN2 != BN2*BN1 \n");
	}else printf("Test 8 passed!\n");

  
	// ²âÊÔ (b1 * b2) * b3 == b1* (b2*b3)	
	F12_multiply(&TN1,BN1,BN2);	
	F12_multiply(&TN1,TN1,BN3);
	F12_multiply(&TN2,BN2,BN3);
	F12_multiply(&TN2,BN1,TN2);

	if(!F12_equal(TN1,TN2))
	{
		printf("BNField12 test: (BN1 * BN2) * BN3 != BN1* (BN2*BN3) \n");
	}else printf("Test 9 passed!\n");

	// ²âÊÔ (b1 * b2) * k == b1* (b2*k)	
 
	F12_multiply(&TN1,BN1,BN2);
	F12_multiply_F4(&TN1,TN1,B1);
	F12_multiply_F4(&TN2,BN2,B1);
	F12_multiply(&TN2,BN1,TN2);
	if(!F12_equal(TN1,TN2))
	{
		printf("BNField12 test: (BN1 * BN2) * B1 != BN1* (BN2*B1)  \n");
	}else printf("Test 10 passed!\n");	

	// ²âÊÔ (b1 * b2) * i == b1* (b2*i)	
	F12_multiply(&TN1,BN1,BN2);
	F12_multiply_i(&TN1,TN1,5);
	F12_multiply_i(&TN2,BN2,5);
	F12_multiply(&TN2,BN1,TN2);
	if(!F12_equal(TN1,TN2))
	{
		printf("BNField12 test: (BN1 * BN2) * i != BN1* (BN2*i)	 \n");
	}else printf("Test 11 passed!\n");
    
	

	// ²âÊÔb1 ^2 == b1*b1	

	F12_square(&TN1,BN1);
	F12_multiply(&TN2,BN1,BN1);

	if(!F12_equal(TN1,TN2))
	{
		printf("BNField12 test: BN1 ^2 != BN1*BN1	 \n");
	}else printf("Test 12 passed!\n");

	// ²âÊÔb1 *b1^(-1) == 1	

	F12_inverse(&TN1,BN1);
   //F12_toString(TN1,HEX);
	//F12_toString_d(TN1,HEX);
	F12_multiply(&TN1,TN1,BN1);
	//F12_toString(TN1,HEX);
//  F12_toString_d(TN1);
	if(!F12_isOne(TN1))
	{
		printf("BNField12 test: BN1 *BN1^(-1) != 1 \n");
	}else printf("Test 13 passed!\n");	
/* 
*/
	printf("BNField12 test: over! \n");
}

void test_BNField4()
{
	CBigInt a,b,c,d,e,f;
//	mpz_t a1,b1,c1,d1,e1,f1;
	BNField2 b1,b2,b3,b4,b5,b6;
	BNField2 t1,t2,t3,t4,t5,t6;
	BNField4 B1,B2,B3,T1,T2,T3;
	
	Get(&a,"93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD",HEX);
	Get(&b,"21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616",HEX);
	Get(&c,"85AEF3D078640C98597B6027B441A01FF1DD2C190F5E93C454806C11D8806141",HEX);
	Get(&d,"3722755292130B08D2AAB97FD34EC120EE265948D19C17ABF9B7213BAF82D65B",HEX);
	Get(&e,"17509B092E845C1266BA0D262CBEE6ED0736A96FA347C8BD856DC76B84EBEB96",HEX);
	Get(&f,"A7CF28D519BE3DA65F3170153D278FF247EFBA98A71A08116215BBA5C999A7C7",HEX);

	printf("BNField4 test: Begin! \n");

	F2_construct(&b1,a, b);
	
	F2_construct(&b2,BN.ZERO,BN.ZERO);
 
	F4_construct(&B1,b1, b2);
    F4_construct_F2(&B2,b1);
  // F4_toString(B1,HEX);
  // F4_toString(B2,HEX);
	if(!F4_equal(B1,B2))
	{
		printf("BNField4 construction: B1 != B2\n");

	}else printf("Test 1 passed!\n");

    F2_construct(&b1,a,b);
    F2_construct(&b2,a,c);
	F2_construct(&b3,a,d);
    F2_construct(&t1,a,b);
    F2_construct(&t2,b,d);
	F2_construct(&t3,b,f);

    F4_construct(&B1,b1,t1);
    F4_construct(&B2,b2,t2);
	F4_construct(&B3,b3,t3);
    
	//F4_toString(B1,HEX);
	//F4_toString(B2,HEX);
   // F4_toString(B3,HEX);

	F4_add(&T1,B1,B2);
    F4_add(&T2,B2,B1);
	

	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: B1+B2 != B2+B1 \n");

	}else printf("Test 2 passed!\n");

	F4_add(&T1,T1,B3);
    F4_add(&T2,B2,B3);
    F4_add(&T2,T2,B1);

	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: (B1+B2)+B3 != B1+(B2+B3) \n");

	}else printf("Test 3 passed!\n");
 
    F4_add(&T1,B1,B2);
	F4_add_F2(&T1,T1,b1);
    F4_add_F2(&T2,B2,b1);
    F4_add(&T2,B1,T2);	
	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: (B1+B2)+k != B1+(B2+k) \n");
	}else printf("Test 4 passed!\n");

    // ²âÊÔb1 - b2 == -(b2 - b1) 
    F4_substract(&T1,B1,B2);
    F4_substract(&T2,B2,B1);
	F4_negate(&T2,T2);
	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: B1 - B2 != -(B2 - B1) \n");
	}else printf("Test 5 passed!\n");

   // ²âÊÔ b1 - b1 == 0
    F4_substract(&T1,B1,B1);
	if(!F4_isZero(T1))
	{
		printf("BNField4 test: B1 - B1 != 0 \n");
	}else printf("Test 6 passed!\n");

    // ²âÊÔ b1 * 2  != b1 + b1
    F4_add(&T1,B1,B1);  
	F4_multiply_i(&T2,B1,2);
	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: B1 * 2  != B1 + B1 \n");
	}else printf("Test 7 passed!\n");

    
   // ²âÊÔ b1 * b2 == b2*b1

	F4_multiply(&T1,B1,B2);
	F4_multiply(&T2,B2,B1);

	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: B1 * B2 != B2*B1 \n");
	}else printf("Test 8 passed!\n");

  
	// ²âÊÔ (b1 * b2) * b3 == b1* (b2*b3)	
	F4_multiply(&T1,B1,B2);
	F4_multiply(&T1,T1,B3);
	F4_multiply(&T2,B2,B3);
	F4_multiply(&T2,B1,T2);
	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: (B1 * B2) * B3 != B1* (B2*B3) \n");
	}else printf("Test 9 passed!\n");
 
	// ²âÊÔ (b1 * b2) * k == b1* (b2*k)	


	F4_multiply(&T1,B1,B2);
	F4_multiply_F2(&T1,T1,b1);
	F4_multiply_F2(&T2,B2,b1);
	F4_multiply(&T2,B1,T2);
	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: (B1 * B2) * b1 != B1* (B2*b1)  \n");
	}else printf("Test 10 passed!\n");


	// ²âÊÔ (b1 * b2) * i == b1* (b2*i)	
	F4_multiply(&T1,B1,B2);
	F4_multiply_i(&T1,T1,5);
	F4_multiply_i(&T2,B2,5);
	F4_multiply(&T2,B1,T2);
	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: (B1 * B2) * i != B1* (B2*i)	 \n");
	}else printf("Test 11 passed!\n");
   
	
	// ²âÊÔ (b1 * b2) * u == b1* (b2*u)	

	F4_multiply(&T1,B1,B2);
	F4_multiply_v(&T1,T1);
	F4_multiply_v(&T2,B2);
	F4_multiply(&T2,B1,T2);
	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: (B1 * B2) * v != B1* (B2*v)	 \n");
	}else printf("Test 12 passed!\n");
 
	
	// ²âÊÔb1 ^2 == b1*b1	

	F4_square(&T1,B1);
	F4_multiply(&T2,B1,B1);

	if(!F4_equal(T1,T2))
	{
		printf("BNField4 test: B1 ^2 != B1*B1	 \n");
	}else printf("Test 13 passed!\n");

	// ²âÊÔb1 *b1^(-1) == 1	

	F4_inverse(&T1,B1);
	//F4_toString(T1,DEC);
	F4_multiply(&T1,T1,B1);

	if(!F4_isOne(T1))
	{
		printf("BNField4 test: B1 *B1^(-1) != 1		 \n");
	}else printf("Test 14 passed!\n");
  
/**/
	printf("BNField4 test: over! \n");


}

void test_BNField2()
{
	CBigInt a,b,c,d,e,f;
	BNField2 b1,b2,b3,t1,t2,t3;
/*
    b1 = BNField2_init();
    b2 = BNField2_init();
	b3 = BNField2_init();
	t1 = BNField2_init();
	t2 = BNField2_init();
	t3 = BNField2_init();
	*/
	Get(&a,"93DE051D62BF718FF5ED0704487D01D6E1E4086909DC3280E8C4E4817C66DDDD",HEX);
	Get(&b,"21FE8DDA4F21E607631065125C395BBC1C1C00CBFA6024350C464CD70A3EA616",HEX);
	Get(&c,"85AEF3D078640C98597B6027B441A01FF1DD2C190F5E93C454806C11D8806141",HEX);
	Get(&d,"3722755292130B08D2AAB97FD34EC120EE265948D19C17ABF9B7213BAF82D65B",HEX);
	Get(&e,"17509B092E845C1266BA0D262CBEE6ED0736A96FA347C8BD856DC76B84EBEB96",HEX);
	Get(&f,"A7CF28D519BE3DA65F3170153D278FF247EFBA98A71A08116215BBA5C999A7C7",HEX);

	printf("BNField2 test: Begin! \n");

	//printf("a = %s\n",Put(a,DEC));
	//printf("b = %s\n",Put(b,DEC));

	F2_construct(&b1,a,b);
   // F2_toString(b1,DEC);
	//printf("\n");
	//F2_toString(b1,HEX);

	F2_construct(&b1,b,BN.ZERO);
    F2_construct_I(&b2,b);

	if(!F2_equal(b1,b2))
	{
		printf("construction: b1 != b2\n");

	}else printf("Test 1 passed!\n");

    F2_construct(&b1,a,b);
    F2_construct(&b2,c,d);
	F2_construct(&b3,e,f);

	F2_add(&t1,b1,b2);
  
    F2_add(&t2,b2,b1);

	if(!F2_equal(t1,t2))
	{
		printf("BNField2 test: b1+b2 != b2+b1 \n");

	}else printf("Test 2 passed!\n");

	F2_add(&t1,t1,b3);
    F2_add(&t2,b2,b3);
    F2_add(&t2,t2,b1);
	if(!F2_equal(t1,t2))
	{
		printf("BNField2 test: (b1+b2)+b3 != b1+(b2+b3) \n");

	}else printf("Test 3 passed!\n");

    F2_add(&t1,b1,b2);
	F2_add_I(&t1,t1,a);
    F2_add_I(&t2,b2,a);
    F2_add(&t2,b1,t2);	
	if(!F2_equal(t1,t2))
	{
		printf("BNField2 test: (b1+b2)+k != b1+(b2+k) \n");
	}else printf("Test 4 passed!\n");
   // ²âÊÔb1 - b2 == -(b2 - b1) 
    F2_substract(&t1,b1,b2);
    F2_substract(&t2,b2,b1);
	F2_negate(&t2,t2);
	if(!F2_equal(t1,t2))
	{
		printf("BNField2 test: b1 - b2 != -(b2 - b1) \n");
	}else printf("Test 5 passed!\n");

   // ²âÊÔ b1 - b1 == 0
    F2_substract(&t1,b1,b1);
	if(!F2_isZero(t1))
	{
		printf("BNField2 test: b1 - b1 != 0 \n");
	}else printf("Test 6 passed!\n");
   
    F2_add(&t1,b1,b1);  
	F2_multiply_i(&t2,b1,2);
	if(!F2_equal(t1,t2))
	{

		printf("BNField2 test: b1 * 2  != b1 + b1 \n");
	}else printf("Test 7 passed!\n");
 
    
   // ²âÊÔ b1 * b2 == b2*b1
	F2_multiply(&t1,b1,b2);
	F2_multiply(&t2,b2,b1);
	if(!F2_equal(t1,t2))
	{
		printf("BNField2 test: b1 * b2 != b2*b1 \n");
	}else printf("Test 8 passed!\n");

 
	// ²âÊÔ (b1 * b2) * b3 == b1* (b2*b3)	
	F2_multiply(&t1,b1,b2);
	F2_multiply(&t1,t1,b3);
	F2_multiply(&t2,b2,b3);
	F2_multiply(&t2,b1,t2);
	if(!F2_equal(t1,t2))
	{
		printf("BNField2 test: (b1 * b2) * b3 != b1* (b2*b3) \n");
	}else printf("Test 9 passed!\n");

	// ²âÊÔ (b1 * b2) * k == b1* (b2*k)	
	F2_multiply(&t1,b1,b2);
	F2_multiply_I(&t1,t1,a);
	F2_multiply_I(&t2,b2,a);
	F2_multiply(&t2,b1,t2);
	if(!F2_equal(t1,t2))
	{
		printf("BNField2 test: (b1 * b2) * k != b1* (b2*k)	 \n");
	}else printf("Test 10 passed!\n");


	// ²âÊÔ (b1 * b2) * i == b1* (b2*i)	
	F2_multiply(&t1,b1,b2);
	F2_multiply_i(&t1,t1,5);
	F2_multiply_i(&t2,b2,5);
	F2_multiply(&t2,b1,t2);
	if(!F2_equal(t1,t2))
	{
		printf("BNField2 test: (b1 * b2) * i != b1* (b2*i)	 \n");
	}else printf("Test 11 passed!\n");
    
	
	// ²âÊÔ (b1 * b2) * u == b1* (b2*u)	

	F2_multiply(&t1,b1,b2);
	F2_multiply_u(&t1,t1);
	F2_multiply_u(&t2,b2);
	F2_multiply(&t2,b1,t2);
	if(!F2_equal(t1,t2))
	{
		printf("BNField2 test: (b1 * b2) * u != b1* (b2*u)	 \n");
	}else printf("Test 12 passed!\n");

	// ²âÊÔb1 ^2 == b1*b1	

	F2_square(&t1,b1);
	F2_multiply(&t2,b1,b1);

	if(!F2_equal(t1,t2))
	{
		printf("BNField2 test: b1 ^2 != b1*b1	 \n");
	}else printf("Test 13 passed!\n");

	// ²âÊÔb1 *b1^(-1) == 1	
	
	F2_inverse(&t1,b1);
	F2_multiply(&t1,t1,b1);

	if(!F2_isOne(t1))
	{
		printf("BNField2 test: b1 *b1^(-1) != 1		 \n");
	}else printf("Test 14 passed!\n");
   
/* */
	printf("BNField2 test: over! \n");

}
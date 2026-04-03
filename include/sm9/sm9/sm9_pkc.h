#ifndef SM9PKC_H
#define SM9PKC_H

#include "sm9/sm9/sm9_ka.h"
#include "sm9/hash/sm4.h"

void KEM_demo();

/*
  mode: 0 = encrypt with sender ID, 1 = encrypt with receiver ID
*/
void PKC_demo(int mode);

/*
   deB: Private key generated
   ke: User's private key
   ID: User ID string
   P2: Generator of group G2
*/
void PKC_Keygen(BNPoint2 *deB, CBigInt ke, BYTE *ID, BNPoint2 P2);

/*
Key encapsulation algorithm:
K: Encapsulated key
C: Ciphertext of encapsulation
*/
void PKC_kem(BYTE *K, BNPoint *C, BYTE *ID, BNPoint P1, BNPoint2 P2, BNPoint P_pub_e, unsigned int klen);

/*
Key decapsulation algorithm:
K: Decapsulated key
klen: Length of K in bytes
*/
void PKC_kom(BYTE *K, BNPoint C, BNPoint2 deB, BYTE *ID, unsigned int klen);

#endif

#ifndef UTILITY_H
#define UTILITY_H

#include "sm9/hash/sm3.h"
#include "sm9/curve/pairing.h"


// XOR two byte arrays
void Bytes_XOR(BYTE *b, BYTE *b1, BYTE *b2,unsigned int len);
/*
  K: 256-bit MAC value
  len1: Length of Z in bytes
  len2: Length of K2 in bytes
*/
void MAC(BYTE *K,BYTE *Z, unsigned len1,BYTE *K2, int len2);

// Check if two byte arrays are equal
int Bytes_Equal(BYTE *b1, BYTE *b2,int len);

// Print byte array
void printByte(BYTE* b,int len);

// Convert point P to 64-byte array (P must be normalized)
void PtoByte(BYTE *b,BNPoint P);
/*
  k: Generated shared key
  msg: Pointer to message bytes
  msglen: Length of message in bytes
  klen: Required length of shared key
*/
void KDF(BYTE *k, BYTE *msg, unsigned int msgLengh, unsigned int klen);

/*
  h1: Output hash value
  msg: Pointer to message bytes
  len: Length of message in bytes
  n: Usually the order N of the group
*/
void Hash_1(CBigInt *h1, BYTE *msg, unsigned int len, CBigInt n);

void Hash_2(CBigInt *h1, BYTE *msg, unsigned int len, CBigInt n);

// Convert hex string to byte array, length must be even, msg length = length/2
void Hex2Byte(BYTE *msg, BYTE *hex, int length);

/*
Convert 12th extension field element to byte array, msg size is 384 bytes
*/
void F12toByte(BYTE *msg,BNField12 b);

// Calculate (a-b) mod N
void CBigInt_substract_modN(CBigInt *X, CBigInt a, CBigInt b);

#endif

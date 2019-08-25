#include "utility.h"
#include <time.h>

void DSA_Demo();

void DSA_Keygen(BNPoint *dsA,CBigInt ks, BYTE *ID,BNPoint P1);

void DSA_Sign(CBigInt *h, BNPoint *S, BYTE *M,BNPoint P1, BNPoint2 P_pub, BNPoint dsA);

int DSA_Verify(CBigInt *h2, CBigInt h, BNPoint S, BYTE *M, BYTE *ID,BNPoint P1, BNPoint2 P2, BNPoint2 P_pub);
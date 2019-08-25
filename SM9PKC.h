#include "SM9KA.h"
#include "sm4.h"

void KEM_demo();

/*
  mode: 0,采用序列密码方式加密； 1，采用分组密码方式加密
*/
void PKC_demo(int mode);


/*
   deB:生成的私钥
   ke:主私钥
   ID:身份ID字符串
   P2：群G2的生成元

*/
void PKC_Keygen(BNPoint2 *deB,CBigInt ke, BYTE *ID,BNPoint2 P2);

/*
密钥封装算法：
K：被封装的密钥
C：封装的密文

*/
void PKC_kem(BYTE *K,BNPoint *C,BYTE *ID,BNPoint P1,BNPoint2 P2,BNPoint P_pub_e,unsigned int klen);

/*
密钥解封装算法：
K:被解封的密钥
klen：K的字节长度
*/
void PKC_kom(BYTE *K, BNPoint C,BNPoint2 deB,BYTE *ID,unsigned int klen);
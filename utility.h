#include "SM3.h"
#include "BNPairing.h"



//对两个字节数组进行异或运算
void Bytes_XOR(BYTE *b, BYTE *b1, BYTE *b2,unsigned int len);
/*
  K:256位的MAC值
  len1: Z的字节数
  len2: K2的字节数
*/
void MAC(BYTE *K,BYTE *Z, unsigned len1,BYTE *K2, int len2);

//判断两个字节数组是否相等
int Bytes_Equal(BYTE *b1, BYTE *b2,int len);

//打印显示Byte数组
void printByte(BYTE* b,int len);

//将点P转换为64个字节串，注意P需为规范型
void PtoByte(BYTE *b,BNPoint P);
/*
  k：生成的共享密钥
  msg:输入消息的字节指针
  msglen:输入消息的字节长度
  klen : 需要获取的共享密钥的比特长度
*/
void KDF(BYTE *k, BYTE *msg, unsigned int msgLengh, unsigned int klen);

/*
  h1：函数返回值
  msg:输入消息的字节指针
  len:输入消息的字节长度
  n : 通常为大整数N
*/
void Hash_1(CBigInt *h1, BYTE *msg, unsigned int len, CBigInt n);

void Hash_2(CBigInt *h1, BYTE *msg, unsigned int len, CBigInt n);

//将16进制字符串转换为BYTE数组，注意length需要为偶数，转换后msg的长度为lenth/2
void Hex2Byte(BYTE *msg, BYTE *hex, int length);

/*
把12次扩域元素转换为BYTE数组，得到大小为384字节大小的msg
*/
void F12toByte(BYTE *msg,BNField12 b);

//计算（a-b）mod N
void CBigInt_substract_modN(CBigInt *X, CBigInt a, CBigInt b);
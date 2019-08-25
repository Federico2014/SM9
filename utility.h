#include "SM3.h"
#include "BNPairing.h"



//�������ֽ���������������
void Bytes_XOR(BYTE *b, BYTE *b1, BYTE *b2,unsigned int len);
/*
  K:256λ��MACֵ
  len1: Z���ֽ���
  len2: K2���ֽ���
*/
void MAC(BYTE *K,BYTE *Z, unsigned len1,BYTE *K2, int len2);

//�ж������ֽ������Ƿ����
int Bytes_Equal(BYTE *b1, BYTE *b2,int len);

//��ӡ��ʾByte����
void printByte(BYTE* b,int len);

//����Pת��Ϊ64���ֽڴ���ע��P��Ϊ�淶��
void PtoByte(BYTE *b,BNPoint P);
/*
  k�����ɵĹ�����Կ
  msg:������Ϣ���ֽ�ָ��
  msglen:������Ϣ���ֽڳ���
  klen : ��Ҫ��ȡ�Ĺ�����Կ�ı��س���
*/
void KDF(BYTE *k, BYTE *msg, unsigned int msgLengh, unsigned int klen);

/*
  h1����������ֵ
  msg:������Ϣ���ֽ�ָ��
  len:������Ϣ���ֽڳ���
  n : ͨ��Ϊ������N
*/
void Hash_1(CBigInt *h1, BYTE *msg, unsigned int len, CBigInt n);

void Hash_2(CBigInt *h1, BYTE *msg, unsigned int len, CBigInt n);

//��16�����ַ���ת��ΪBYTE���飬ע��length��ҪΪż����ת����msg�ĳ���Ϊlenth/2
void Hex2Byte(BYTE *msg, BYTE *hex, int length);

/*
��12������Ԫ��ת��ΪBYTE���飬�õ���СΪ384�ֽڴ�С��msg
*/
void F12toByte(BYTE *msg,BNField12 b);

//���㣨a-b��mod N
void CBigInt_substract_modN(CBigInt *X, CBigInt a, CBigInt b);
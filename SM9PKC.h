#include "SM9KA.h"
#include "sm4.h"

void KEM_demo();

/*
  mode: 0,�����������뷽ʽ���ܣ� 1�����÷������뷽ʽ����
*/
void PKC_demo(int mode);


/*
   deB:���ɵ�˽Կ
   ke:��˽Կ
   ID:���ID�ַ���
   P2��ȺG2������Ԫ

*/
void PKC_Keygen(BNPoint2 *deB,CBigInt ke, BYTE *ID,BNPoint2 P2);

/*
��Կ��װ�㷨��
K������װ����Կ
C����װ������

*/
void PKC_kem(BYTE *K,BNPoint *C,BYTE *ID,BNPoint P1,BNPoint2 P2,BNPoint P_pub_e,unsigned int klen);

/*
��Կ���װ�㷨��
K:��������Կ
klen��K���ֽڳ���
*/
void PKC_kom(BYTE *K, BNPoint C,BNPoint2 deB,BYTE *ID,unsigned int klen);
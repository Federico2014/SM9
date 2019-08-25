
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//��������1024λ�������ƣ����м���
#ifndef BI_MAXLEN
#define BI_MAXLEN 32
#define DEC 10
#define HEX 16

//typedef long long __int64;
typedef struct CBigInt_Tag{
//������0x100000000�����µĳ���    
unsigned m_nLength;
//�������¼������0x100000000������ÿһλ��ֵ
unsigned long m_ulValue[BI_MAXLEN];
}CBigInt;



/*****************************************************************
��������������
Init, ����������󲢳�ʼ��Ϊ��
Mov����ֵ���㣬�ɸ�ֵΪ��������ͨ������������Ϊ�������=��
Cmp���Ƚ����㣬������Ϊ�������==������!=������>=������<=����
Add���ӣ��������������������ͨ�����ĺͣ�������Ϊ�������+��
Sub�������������������������ͨ�����Ĳ������Ϊ�������-��
Mul���ˣ��������������������ͨ�����Ļ���������Ϊ�������*��
Div�������������������������ͨ�������̣�������Ϊ�������/��
Mod��ģ���������������������ͨ������ģ��������Ϊ�������%��
*****************************************************************/
void CBigIntInit(CBigInt *A);
void Mov_Big_Long(CBigInt * N, unsigned long A);
void Mov_Big_Big(CBigInt *N, CBigInt A);
void Add_Big_Big(CBigInt *Y, CBigInt N, CBigInt A);
void Add_Big_Long(CBigInt *Y, CBigInt N, unsigned long A);
void Sub_Big_Big(CBigInt *Y,CBigInt N, CBigInt A);
void Sub_Big_Long(CBigInt *Y, CBigInt N, unsigned long A);
void Mul_Big_Big(CBigInt *Y, CBigInt N, CBigInt A);
void Mul_Big_Long(CBigInt *Y, CBigInt N, unsigned long A);
void Div_Big_Big(CBigInt *M,CBigInt N, CBigInt A);
void Div_Big_Long(CBigInt *Y, CBigInt N, unsigned long A);
void Mod_Big_Big(CBigInt *Z,CBigInt N, CBigInt A);
unsigned long Mod_Big_Long(CBigInt N, unsigned long A);
int Cmp(CBigInt N,CBigInt A);

/*****************************************************************
�������
Get�����ַ�����10���ƻ�16���Ƹ�ʽ���뵽����
Put����������10���ƻ�16���Ƹ�ʽ������ַ���
*****************************************************************/
void Get(CBigInt *N, char* str, unsigned int system);
char* Put(CBigInt N, unsigned int system);
unsigned char* PutFieldElement(CBigInt N, unsigned int system);//��Ҫ��ʾ����Ԫ�أ������λΪ0����Ԫ�ز�0��ʾ
/*****************************************************************
Euc��ŷ������㷨���ͬ�෽��
Exp������ƽ���㷨������ģ����
*****************************************************************/
void Inv(CBigInt *Z, CBigInt N, CBigInt A);
void Exp(CBigInt *Z, CBigInt N, CBigInt A, CBigInt B);
#endif

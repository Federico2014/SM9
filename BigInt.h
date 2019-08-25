
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//允许生成1024位（二进制）的中间结果
#ifndef BI_MAXLEN
#define BI_MAXLEN 32
#define DEC 10
#define HEX 16

//typedef long long __int64;
typedef struct CBigInt_Tag{
//大数在0x100000000进制下的长度    
unsigned m_nLength;
//用数组记录大数在0x100000000进制下每一位的值
unsigned long m_ulValue[BI_MAXLEN];
}CBigInt;



/*****************************************************************
基本操作与运算
Init, 构造大数对象并初始化为零
Mov，赋值运算，可赋值为大数或普通整数，可重载为运算符“=”
Cmp，比较运算，可重载为运算符“==”、“!=”、“>=”、“<=”等
Add，加，求大数与大数或大数与普通整数的和，可重载为运算符“+”
Sub，减，求大数与大数或大数与普通整数的差，可重载为运算符“-”
Mul，乘，求大数与大数或大数与普通整数的积，可重载为运算符“*”
Div，除，求大数与大数或大数与普通整数的商，可重载为运算符“/”
Mod，模，求大数与大数或大数与普通整数的模，可重载为运算符“%”
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
输入输出
Get，从字符串按10进制或16进制格式输入到大数
Put，将大数按10进制或16进制格式输出到字符串
*****************************************************************/
void Get(CBigInt *N, char* str, unsigned int system);
char* Put(CBigInt N, unsigned int system);
unsigned char* PutFieldElement(CBigInt N, unsigned int system);//主要显示基域元素，将最低位为0的域元素补0显示
/*****************************************************************
Euc，欧几里德算法求解同余方程
Exp，反复平方算法进行幂模运算
*****************************************************************/
void Inv(CBigInt *Z, CBigInt N, CBigInt A);
void Exp(CBigInt *Z, CBigInt N, CBigInt A, CBigInt B);
#endif

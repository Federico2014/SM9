#include "BNPoint2.h"


void Line_Funtion(BNField12 *f, BNPoint2 T, BNPoint2 Q, BNPoint P); // �ߺ����ļ��� 

void Final_exp(BNField12 *f, BNField12 p); //�����ݵļ��� f = b^((b^12-1)/12)

void Pairing_opt(BNField12 *f,BNPoint2 Q, BNPoint P); //���ŶԵļ���

void Pairing_Rate(BNField12 *f, BNPoint2 Q, BNPoint P); // Rate �Եļ���
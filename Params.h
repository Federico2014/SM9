#include "BigInt.h"

struct SM9Params
{
    CBigInt t;
	CBigInt q;
	CBigInt n;
	CBigInt tr;   //trace
	CBigInt ord;  // order = 6t+2
	CBigInt exp_6t_5;  // exp1 = 6t+5;
	CBigInt exp_6t_2_1;   // exp2  = 6t^2 + 1
	CBigInt q_1_12;  //(q-1)/12
	CBigInt q12_1_12;   //(q^12-1)/12
	CBigInt exp_64;     // 64^q_1_12
	CBigInt exp__8;    //  (-8)^q_1_12
	CBigInt exp__2;   //  (-2)^q_1_12
    CBigInt exp_4;    //  (4)^q_1_12
	//CBigInt exp_64_e6; 
	CBigInt ZERO;
	CBigInt ONE;

}BN;



 void SM9Params_init(struct SM9Params *bn);
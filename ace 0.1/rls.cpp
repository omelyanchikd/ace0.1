#include "rls.h"


rls::rls(void)
{
}


void rls::update(matrix y, matrix x)
{
	fi = fi + (1.0 / (1 + double(x * p * x.transpose()))) * p * x.transpose() * (y - x * fi);  
	p = (identity + ((-1.0 / (1 + double(x * p * x.transpose()))) * p * x.transpose()) * x) * p;
}
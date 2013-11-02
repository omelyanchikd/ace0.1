#include "rls.h"


rls::rls(void)
{
	_identity = (matrix(0));
	_fi = (matrix(0));
	_p = (matrix(0));
}

rls::rls(vector<double> fi, matrix p)
{
	_fi = matrix(fi);
	_p = p;
}


void rls::update(double y, vector<double> x)
{
	matrix _x = matrix(x);
//	matrix _y = matrix(y);
	_fi = _fi + (1.0 / (1 + double(_x * _p * _x.transpose()))) * _p * _x.transpose() * (y - double(_x * _fi.transpose()));  
	_p = (_identity + ((-1.0 / (1 + double(_x * _p * _x.transpose()))) * _p * _x.transpose()) * _x) * _p;
}

vector<double> rls::get_action(vector<double> x)
{
	return (vector<double>(matrix(x) * _fi.transpose()));
}

vector<double> rls::get_action()
{
	return (vector<double>(_fi));
}
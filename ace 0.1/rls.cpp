#include "rls.h"


rls::rls(void)
{
	_identity = (matrix(0));
	_fi = (matrix(0));
	_p = (matrix(0));
	_forgetting = 0;
}

rls::rls(vector<double> fi, matrix p)
{
	_fi = matrix(fi);
	_p = p;
	_forgetting = 0.5;
}


void rls::update(double y, vector<double> x)
{
	matrix _x = matrix(x);
//	matrix _y = matrix(y);
	double var1 = double(_x * _fi.transpose());
	double var2 = double(_x * _p * _x.transpose());
	matrix var3 = _p * _x.transpose();
	matrix var4 = (1/(1+var2)) * var3;
	matrix var5 = var4 * (y - var1);
	_fi = _fi + ((1.0 / (_forgetting + double(_x * _p * _x.transpose()))) * _p * _x.transpose() * (y - double(_x * _fi.transpose()))).transpose();  
	_p = (_identity + ((1 / (_forgetting + double(_x * _p * _x.transpose()))) * _p * _x.transpose()) * _x) * _p * (1/_forgetting);
}

vector<double> rls::get_action(vector<double> x)
{
	return (vector<double>(matrix(x) * _fi.transpose()));
}

vector<double> rls::get_action()
{
	return (vector<double>(_fi));
}
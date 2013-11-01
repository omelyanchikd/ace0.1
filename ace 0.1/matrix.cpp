#include "matrix.h"


matrix::matrix(void)
{
	_n = 0; 
	_m = 0;
	_a.clear();
}


matrix::matrix(int n, int m)
{
	_n = n;
	_m = m;
	_a.clear();
	for (int i = 0; i < _n * _m; i++)
	{
		_a.push_back(0);
	}
}

matrix::matrix(int n, int m, vector<double> a)
{
	_n = n;
	_m = m;
	_a.clear();
	for (int i = 0; i < _n * _m; i++)
	{
		_a.push_back(a[i]);
	}
}

matrix::matrix(const matrix &b)
{
	_n = b._n;
	_m = b._m;
	for (int i = 0; i < _n * _m; i++)
	{
		_a.push_back(b._a[i]);
	}
}

matrix::matrix(double a)
{
	_n = 1;
	_m = 1;
	_a.push_back(a);
}

matrix::matrix(vector<double> a)
{
	_n = 1;
	_m = a.size();
	for (int i = 0; i < a.size(); i++)
	{
		_a.push_back(a[i]);
	}
}

matrix matrix::operator=(const matrix &b)
{
	if (this == &b)
		return *this;
	_n = b._n;
	_m = b._m;
	_a.clear();
	for (int i = 0; i < _n * _m; i++)
	{
		_a.push_back(b._a[i]);
	}
	return *this;
}

matrix& matrix::operator+=(const matrix& b)
{
	if ((_n != b._n) || (_m != b._m))
		return *this;	
	for (int i = 0; i < _a.size(); i++)		
			_a[i] += b._a[i];
	return *this;
}

matrix matrix::operator+(const matrix &b)
{
	matrix temp(*this);
	return (temp += b);

}

double& matrix::operator()(int i, int j)
{
	return _a[_n * i + j];
}

matrix operator*(const matrix &a, const matrix &b)
{
	if (a._m != b._n)
		return a;
	matrix mult(a._n, b._m);
	for (int i = 0; i < mult._n; i++)
		for (int j = 0; j < mult._m; j++)
			for (int k = 0; k < a._n; k++)
				mult._a[mult._n * i + j] += a._a[a._n * i + k] * b._a[b._n * k + j];
	return mult;

}

matrix operator*(double c, const matrix &b)
{
	matrix mult(b);
	for (int i = 0; i < mult._a.size(); i++)
		mult._a[i] *= c;
	return mult;
}

matrix operator*(const matrix &b, double c)
{
	matrix mult(b);
	for (int i = 0; i < mult._a.size(); i++)
		mult._a[i] *= c;
	return mult;
}

matrix matrix::transpose()
{
	matrix trans(_m, _n);
	for (int i = 0; i < _m; i++)
		for (int j = 0; j < _n; j++)
			trans._a[_m * i + j] = _a[_m * j + i];
	return trans;
}
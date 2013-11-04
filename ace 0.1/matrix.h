#pragma once

#include <vector>

using namespace std;

class matrix
{
public:
	matrix(void);
	matrix (int n, int m);
	matrix(int n, int m, vector<double> a);
	matrix(int n, int m, double *a);
	matrix(const matrix &b);
	matrix(double a);
	matrix(vector<double> a);
	matrix(int n);
	
	matrix operator=(const matrix &b);
	
	matrix& matrix::operator+=(const matrix& b);
	matrix operator+(const matrix &b);
	
	double& operator()(int i, int j); 
	
	friend matrix operator*(const matrix &a, const matrix &b);
	friend matrix operator*(double c, const matrix &b);
	friend matrix operator*(const matrix &b, double c);
	
	matrix transpose();

	operator double() const {if ((_n == 1) && (_m == 1)) return _a[0];}
	operator vector<double>() const {if ((_n == 1) || (_m == 1)) return _a;}

private:
	vector<double> _a;
	int _n, _m;
};


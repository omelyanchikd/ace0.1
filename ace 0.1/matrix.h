#pragma once

#include <vector>

using namespace std;

class matrix
{
public:
	matrix(void);
	matrix (int n, int m);
	matrix(int n, int m, vector<double> a);
	matrix(const matrix &b);
	matrix operator=(const matrix &b);
	matrix& matrix::operator+=(const matrix& b);
	matrix operator+(const matrix &b);
	double& operator()(int i, int j); 
	friend matrix operator*(const matrix &a, const matrix &b);
	friend matrix operator*(double c, const matrix &b);
	friend matrix operator*(const matrix &b, double c);
	matrix transpose();
private:
	vector<double> _a;
	int _n, _m;
};


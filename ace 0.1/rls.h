#pragma once

#include "matrix.h"

class rls
{
public:
	rls(void);
	rls(vector<double> fi, matrix p); 
	void update(vector<double> y, vector<double> x);
	vector<double> get_action(vector<double> x);

private:
	matrix _fi;
	matrix _p;
	matrix _identity;
};


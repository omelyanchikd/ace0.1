#pragma once

#include "matrix.h"

class rls
{
public:
	rls(void);
	void update(matrix y, matrix x);

private:
	matrix fi;
	matrix p;
	matrix identity;
};


#include "vacancy.h"


vacancy::vacancy(void)
{
	_salary = 0;
	_firmid = 0;
}

double vacancy::getsalary()
{
	return _salary;
}

int vacancy::getid()
{
	return _firmid;
}



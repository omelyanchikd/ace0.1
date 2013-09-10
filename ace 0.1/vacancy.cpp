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

int findmatch(int firmid, vector<vacancy> labordemand)
{
	for (int i = 0; i < labordemand.size(); i++)
	{
		if (labordemand[i].getid()==firmid)
			return i;
	}
	return -1;
}

#pragma once

#include <vector>

using namespace std;

class vacancy
{
public:
	vacancy(void);
	vacancy(double salary, int firmid): _salary(salary), _firmid(firmid)
	{
	}
	double getsalary();
	int getid();

private:
	double _salary;
	int _firmid;
};

int findmatch(int firmid, vector<vacancy> labordemand);
#pragma once
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


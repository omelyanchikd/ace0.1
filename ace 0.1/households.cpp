#include "households.h"


households::households(void)
{
}

households::households(int n, double money)
{
	for (int i = 0; i < n; i++)
	{
		_households[i+1] = (household(money));
	}
}

map<int, vector<int>> households::search_work(map<int,double> vacancies)
{
	map<int, vector<int>> resumes;
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); i++)
	{
		resumes[i->first] = (i->second).searchwork(vacancies);
	}
	return resumes;
}

map<int, int> households::choose_employee(map<int, vector<int>> invites, map<int, double> vacancies)
{
	map<int, int> chosen;
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); i++)
	{
		int currentemployee = (i->second).get_employee();
		int employee = (i->second).chooseemployee(invites[i->first], vacancies);
		if ((employee != 0) & (employee != currentemployee))
		{
			chosen[employee] = i->first;
		}
	}
	return chosen;
}

void households::quit(vector<int> fired)
{
	for (int i = 0; i < fired.size(); i++)
	{
		_households[fired[i]].quit();
	}
}

void households::update_salary(map<int, double> salaries)
{
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); i++)
	{
		(i->second).set_salary(salaries[(i->second).get_employee()]);
	}
}

void households::get_income()
{
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); i++)
	{
		if ((i->second).is_employed())
			(i->second).work();
/*		else
			(i->second).gethelp();//*/
	}
}

void households::buy(map<int, offer> &demand)
{
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); i++)
	{
		(i->second).buy_goods(demand);
	}
}

void households::write_log(data _log)
{
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); i++)
	{
		_log.sethouseholdsalary(i->first, (i->second).getsalary());
		_log.sethouseholdemployed(i->first, (i->second).is_employed());
		_log.sethouseholdemployee(i->first, (i->second).get_employee());
		_log.sethouseholdmoney(i->first, (i->second).getmoney());
		_log.sethouseholdreservation(i->first, (i->second).getreservation());
		_log.sethouseholdconsumption(i->first, (i->second).getconsumption());
	}
}

void households::clear()
{
	_households.clear();
}

void households::print_info()
{
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); i++)
	{
		cout<<"Household "<<i->first<<": "<<endl;
		(i->second).printinfo();
	}
}

double households::unemployment()
{
	int unemployed = 0;
	int household_number = 0;
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); i++)
	{
		if (!(i->second).is_employed())
		{
			unemployed++;
		}
		household_number++;
	}
	return (double)unemployed/household_number;
}
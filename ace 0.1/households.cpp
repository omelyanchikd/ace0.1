#include "households.h"


households::households(void)
{
}

households::households(int n, double money, string model_name)
{
	for (int i = 0; i < n; i++)
	{
		_households[i+1] = (household(money));
	}
	ofstream fout;
	ostringstream fn;
	fn<<model_name<<"_unemployment_rate.txt";
	fout.open(fn.str());
	fout.clear();
	fout.close();
	fn.str("");
	fn<<model_name<<"_household_number.txt";
	fout.open(fn.str());
	fout.clear();
	fout.close();
	fn.str("");
	_last_id = n;
}

map<int, vector<int>> households::search_work(map<int,double> vacancies)
{
	map<int, vector<int>> resumes;
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); ++i)
	{
		resumes[i->first] = (i->second).searchwork(vacancies);
	}
	return resumes;
}

map<int, vector<int>> households::choose_employee(map<int, vector<int>> invites, map<int, double> vacancies)
{
	map<int, vector<int>> chosen;
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); ++i)
	{
		int current_employee = (i->second).get_employee();
		int employee = (i->second).chooseemployee(invites[i->first], vacancies);
		if ((employee != 0))// & (employee != current_employee))
		{
			chosen[employee].push_back(i->first);
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
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); ++i)
	{
		if ((i->second).is_employed())
		{
			(i->second).set_salary(salaries[i->first]);
		}
	}
}

void households::get_income()
{
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); ++i)
	{
		if ((i->second).is_employed())
			(i->second).work();
//		else
		//	(i->second).gethelp();//*/
	}
}

void households::buy(map<int, offer> &demand)
{
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); ++i)
	{
		(i->second).buy_goods(demand);
	}
}

void households::write_log(data& _log)
{
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); ++i)
	{
		_log.sethouseholdsalary(i->first, (i->second).getsalary());
		_log.sethouseholdemployed(i->first, (i->second).is_employed());
		_log.sethouseholdemployee(i->first, (i->second).get_employee());
		_log.sethouseholdmoney(i->first, (i->second).getmoney());
		_log.sethouseholdreservation(i->first, (i->second).getreservation());
		_log.sethouseholdconsumption(i->first, (i->second).getconsumption());
	}
}

void households::write_log(string model_name)
{
	ofstream fout;
	ostringstream fn;
	fn<<model_name<<"_unemployment_rate.txt";
	fout.open(fn.str(), ios_base::app);
	fout<<unemployment()<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_household_number.txt";
	fout.open(fn.str(), ios_base::app);
	fout<<household_number()<<" ";
	fout.close();
	fn.str("");
}

void households::clear()
{
	_households.clear();
}

void households::print_info()
{
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); ++i)
	{
		cout<<"Household "<<i->first<<": "<<endl;
		(i->second).printinfo();
	}
}

double households::unemployment()
{
	int unemployed = 0;
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); ++i)
	{
		if (!(i->second).is_employed())
		{
			unemployed++;
		}
	}
	if (household_number())
		return (double)unemployed/household_number();
	return 0;
}

int households::household_number()
{
	return _households.size();
}

void households::die()
{
	vector<int> dead;
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); ++i)
	{
		if ((i->second).get_starve() > 3)
		{
			(i->second).quit();
			dead.push_back(i->first);
		}
	}
	for (int i = 0; i < dead.size(); i++)
	{
		_households.erase(dead[i]);
	}
}

void households::birth()
{
	for (map<int, household>::iterator i = _households.begin(); i != _households.end(); ++i)
	{
		if ((i->second).get_fed() > 5)
		{
			(i->second).set_fed(0);
			_households[_last_id] = (household((i->second).getmoney()));
			_last_id++;		
		}
	}
}
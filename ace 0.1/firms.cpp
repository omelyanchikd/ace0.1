#include "firms.h"


firms::firms(void)
{
}

firms::firms(int n, double money)
{
	for (int i = 0; i < n; i++)
	{
		_firms[i+1] = (firm(money));
	}
}

map<int, double> firms::set_vacancies()
{
	map<int, double> vacancies;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		if ((i->second).getworkers() < (i->second).getdesired())
		{
			vacancies[i->first] = (i->second).getsalary();			
		}
	}
	return vacancies;
}

vector<int> firms::fire()
{
	vector<int> fired;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		if ((i->second).getworkers() > (i->second).getdesired())
		{
			vector<int> decision = (i->second).fire();
			fired.insert(fired.end(),decision.begin(), decision.end());
			decision.clear();
		}
	}
	return fired;
}

map<int, vector<int>> firms::check_resumes(map<int, vector<int>> resumes)
{
	map<int, vector<int>> invites;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		invites[i->first] = (i->second).checkresumes(resumes[i->first]);
	}
	return invites;
}

void firms::hire(map<int, vector<int>> employers)
{
	for (map<int, vector<int>>::iterator i = employers.begin(); i != employers.end(); ++i)
	{
		_firms[i->first].hire(i->second);
	}
}

void firms::produce()
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		(i->second).produce();
	}
}

map<int, offer> firms::set_supply()
{
	map<int, offer> supply;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		supply[i->first] = offer((i->second).getprice(), (i->second).getstock());
	}
	return supply;
}

void firms::get_sales(map<int, int> sales)
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		(i->second).getsales(sales[i->first]);
	}
}

void firms::learn()
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		(i->second).learn();
	}
}

void firms::write_log(data& _log)
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		_log.setfirmsalary(i->first, (i->second).getsalary());
		_log.setfirmprice(i->first, (i->second).getprice());
		_log.setfirmsold(i->first, (i->second).getsold());
		_log.setfirmworkers(i->first, (i->second).getworkers());
		_log.setfirmmoney(i->first, (i->second).getmoney());
		_log.setfirmprofit(i->first, (i->second).getprofit());
		_log.setfirmdesired(i->first, (i->second).getdesired());
		_log.setfirmstock(i->first, (i->second).getstock());	
	}	
}

void firms::clear()
{
	_firms.clear();
}

void firms::print_info()
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		cout<<"Firm "<<i->first<<": "<<endl;
		(i->second).printinfo();
	}
}

double firms::production()
{
	double sum = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		sum += (i->second).getstock(); // * (i->second).getprice();
	}
	return sum;
}

double firms::consumption()
{
	double sum = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		sum += (i->second).getprice() * (i->second).getsold();
	}
	return sum;
}

double firms::average_price()
{
	double sum = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		sum += (i->second).getprice();
	}
	return sum/firm_number();
}

double firms::average_salary()
{
	double sum = 0;
	int workers = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		sum += (i->second).getsalary() * (i->second).getworkers();
		workers += (i->second).getworkers();
	}
	return sum/workers;
}

double firms::gdp()
{
	double sum = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		sum += (i->second).getprice() * (i->second).getstock();
	}
	return sum;
}

int firms::firm_number()
{
	return _firms.size();
}
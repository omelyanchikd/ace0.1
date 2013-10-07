#include "world.h"


world::world(void)
{
}

world::world(int firmnumber, int householdnumber, double firmmoney, double householdmoney)
{
	_firms = (firms(firmnumber, firmmoney));
	_households = (households(householdnumber, householdmoney));
	_goodmarket.clear();
	_labormarket.clear();
}

void world::step()
{
	_firms.fire();
	check_laborinfo();
	for (int iter = 0; iter < 2; iter++)
	{
		_labormarket.set_vacancies(_firms.set_vacancies());
		_labormarket.set_resumes(_households.search_work(_labormarket.get_vacancies()));
		_labormarket.set_invites(_firms.check_resumes(_labormarket.get_resumes()));
		_labormarket.set_employer(_households.choose_employee(_labormarket.get_invites(), _labormarket.get_vacancies()));
		_firms.hire(_labormarket.get_employer());
		_labormarket.clear();
		erase_vacancies();
	}
	_firms.produce();
	_households.get_income();
	_firms.set_supply();
	_households.buy();
	_firms.get_sales();
	get_statistics();
	_firms.write_log(_log);
	_households.write_log(_log);
	_firms.print_info();
	_households.print_info();
	_firms.learn();
	_goodmarket.clear();
	_labormarket.clear();
}

// ����� ��������� �������� �� ����� �����.
void world::set_vacancies()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		if ((i->second).getworkers() > (i->second).getdesired())
		{
			vector<int> fired;
			fired = (i->second).fire();
			for (int j = 0; j < fired.size(); j++)
			{
				households[fired[j]].quit();
			}
		}
		else
		{
			_labormarket.setvacancies(i->first, (i->second).getsalary());	
		}
	}
}


// �������� ���������� �� ��������� �������� � ���������.
void world::check_laborinfo()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		for (int j = 0; j < (i->second).getworkerids().size(); j++)
		{
			households[((i->second).getworkerids())[j]] = (i->second).getsalary();
		}
	}	
}


// ������������� ������������� �������� ����� ������� � ��������, ���� ����������.
void world::set_resumes()
{
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		_labormarket.setresumes((i->second).searchwork(_labormarket.getvacancies()), i->first);
	}
}

// ����� ������������� ������ ���������� � ���������� �� ������ ������������� �����������.
void world::set_invites()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_labormarket.setinvites((i->second).checkresumes(_labormarket.getresumes(i->first)), i->first);
	}
}

// ������������� �������� ����������� ������ � �������� ������������, � ����� �������� �� ������ �������������, ��������� �� �����������.
void world::choose_employer()
{
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		int currentemployee = (i->second).getemployee();
		int employee = (i->second).chooseemployee(_labormarket.getinvites((i->first)), _labormarket.getvacancies());
		if ((employee != 0) & (employee != currentemployee))
		{
			firms[employee].hire(i->first);
		}
	}
}

//����� ���������� ���������
void world::produce()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).produce();
	}
}

//������������� �������� �������� ��� ������� �� �����������
void world::get_income()
{
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		if ((i->second).isemployed())
			(i->second).work();
/*		else
			(i->second).gethelp();//*/
	}
}

//����� ���������� �� ����� ������� ��������� ��� �������
void world::set_supply()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_goodmarket.setsupply((i->second).getprice(), (i->second).getstock(), i->first);
	}
}

//������������� �������� ������ �� ������������
void world::buy()
{
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		(i->second).buygoods(_goodmarket._demand);
	}
}

//����� �������� ���������� �������
void world::get_sales()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).getsales(_goodmarket.getsales(i->first));
	}
}

void world::firm_learning()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).update();
	}
}

void world::write_log()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
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
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		_log. sethouseholdsalary(i->first, (i->second).getsalary());
		_log. sethouseholdemployed(i->first, (i->second).isemployed());
		_log. sethouseholdemployee(i->first, (i->second).getemployee());
		_log. sethouseholdmoney(i->first, (i->second).getmoney());
		_log. sethouseholdreservation(i->first, (i->second).getreservation());
		_log. sethouseholdconsumption(i->first, (i->second).getconsumption());
	}
}

double world::unemployment()
{
	int unemployed = 0;
	int household_number = 0;
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		if (!(i->second).isemployed())
		{
			unemployed++;
		}
		household_number++;
	}
	return (double)unemployed/household_number;
}

double world::production()
{
	double sum = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getstock(); // * (i->second).getprice();
	}
	return sum;
}

double world::consumption()
{
	double sum = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice() * (i->second).getsold();
	}
	return sum;
}

double world::average_price()
{
	double sum = 0;
	int firm_number = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice();
		firm_number++;
	}
	return sum/firm_number;
}

double world::average_salary()
{
	double sum = 0;
	int workers = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getsalary() * (i->second).getworkers();
		workers += (i->second).getworkers();
	}
	return sum/workers;
}

double world::inflation()
{
	double sum = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice() * (i->second).getstock();
	}
	return sum/_statistics.inflation();
}

double world::gdp()
{
	double sum = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice() * (i->second).getstock();
	}
	return sum;
}

void world::get_statistics()
{
	_statistics.set_unemployment(unemployment());		// ������� �����������.
	_statistics.set_production(production());			// ����� ������������.
	_statistics.set_consumption(consumption());			// ����� �����������.
	_statistics.set_average_price(average_price());		// ������� ����.
	_statistics.set_average_salary(average_salary());	// ������� ���������� �����.
	_statistics.set_inflation(inflation());				// ��������.
	_statistics.set_gdp(gdp());							// ������� ���������� �������.
}

void world::erase_vacancies()
{
	map<int, double> vacancies = _labormarket.getvacancies();
	for (map<int, double>::iterator i = vacancies.begin(); i != vacancies.end(); i++)
	{
		if (firms[i->first].getworkers() == firms[i->first].getdesired())
		{
			_labormarket.erase_vacancy(i->first);
		}
	}
}

void world::check_workers()
{
	vector<int> workers;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		
		workers = (i->second).getworkerids();
		for (int j = 0; j < workers.size(); j++)
		{
			if (households[workers[j]].getemployee() != i->first)
			{
				(i->second).fire(workers[j]);
			}
		}
		workers.clear();
	}
}
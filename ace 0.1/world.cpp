#include "world.h"


world::world(void)
{
}

world::world(int firmnumber, int householdnumber, double firmmoney, double householdmoney)
{
	firms.clear();
	households.clear();
	for (int i = 1; i <= firmnumber; i++)
	{
		firms[i] = firm(firmmoney);
	}
	for (int i = 1; i <= householdnumber; i++)
	{
		households[i] = household(householdmoney);
	}
	_goodmarket.clear();
	_labormarket.clear();
}

void world::step()
{
	for (int iter = 0; iter < 2; iter++)
	{
		set_vacancies();
		set_resumes();
		set_invites();
		choose_employer();
		_labormarket.clear();
	}
	produce();
	get_income();
	set_supply();
	buy();
	get_sales();
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_log.setfirmsalary(i->first, (i->second).getsalary());
		_log.setfirmprice(i->first, (i->second).getprice());
		_log.setfirmsold(i->first, (i->second).getsold());
		_log.setfirmworkers(i->first, (i->second).getworkers());
		_log.setfirmmoney(i->first, (i->second).getmoney());
		_log.setfirmsprofit(i->first, (i->second).getprofit());
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
	_goodmarket.clear();
}

void world::printinfo()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		cout<<"Firm "<<i->first<<": "<<endl;
		(i->second).printinfo();
	}
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		cout<<"Household "<<i->first<<": "<<endl;
		(i->second).printinfo();
	}
}

// ����� ��������� �������� �� ����� �����.
void world::set_vacancies()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_labormarket.setvacancies(i->first, (i->second).getsalary());	
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
//		int currentemployee = (i->second).getemployee();
		int employee = (i->second).chooseemployee(_labormarket.getinvites((i->first)), _labormarket.getvacancies());
		if ((employee != 0)) //&& (employee != currentemployee))
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
		else
			(i->second).gethelp();
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
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
		//����� ��������� �������� �� ����� �����
		for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
		{
			_labormarket.setvacancies(i->first, (i->second).postvacancy());	
		}
		//������������� ������������� �������� ����� ������� � ��������, ���� ����������
		for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
		{
			_labormarket.setresumes((i->second).searchwork(_labormarket.getvacancies()), i->first);
		}
		//����� ������������� ������ ���������� � ���������� �� ������ ������������� �����������
		for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
		{
			_labormarket.setinvites((i->second).checkresumes(_labormarket.getresumes(i->first)), i->first);
		}
		//������������� �������� ����������� ������ � �������� ������������, � ����� �������� �� ������ �������������, ��������� �� �����������
		for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
		{
			firms[(i->second).chooseemployee(_labormarket.getresumes((i->first)), _labormarket.getvacancies())].hire(i->first);
		}
		_labormarket.clear();
	}
	//����� ���������� ���������
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).produce();
	}
	//������������� �������� �������� ��� ������� �� �����������
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		if ((i->second).isemployed())
			(i->second).work();
		else
			(i->second).gethelp();
	}
	//����� ���������� �� ����� ������� ��������� ��� �������
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_goodmarket.setsupply((i->second).getprice(), (i->second).getstock(), i->first);
	}
	//������������� �������� ������ �� ������������
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		(i->second).buygoods(_goodmarket.getdemand());
	}
	//����� �������� ���������� �������
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).getsales(_goodmarket.getsales(i->first));
	}
	_goodmarket.clear();
}

void world::printinfo()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		cout<<"Firm "<<i->first<<": ";
		(i->second).printinfo();
	}
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		cout<<"Household "<<i->first<<": ";
		(i->second).printinfo();
	}
}




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
		//firms[i] = firm firmmoney));
	}
	for (int i = 0; i < householdnumber; i++)
	{
		households.push_back(household(i+1, householdmoney));
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
		for (int i = 0; i < households.size(); i++)
		{
			_labormarket.setresumes(households[i].searchwork(_labormarket.getvacancies()), households[i].getid());
		}
		//����� ������������� ������ ���������� � ���������� �� ������ ������������� �����������
		for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
		{
			_labormarket.setinvites((i->second).checkresumes(_labormarket.getresumes(i->first)), i->first);
		}
		//������������� �������� ����������� ������ � �������� ������������, � ����� �������� �� ������ �������������, ��������� �� �����������
		for (int i = 0; i < households.size(); i++)
		{
			firms[households[i].chooseemployee(_labormarket.getresumes(households[i].getid()), _labormarket.getvacancies())].hire(households[i].getid());
		}
		_labormarket.clear();
	}
	//����� ���������� ���������
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).produce();
	}
	//������������� �������� �������� ��� ������� �� �����������
	for (int i = 0; i < households.size(); i++)
	{
		if (households[i].isemployed())
			households[i].work();
		else
			households[i].gethelp();
	}
	//����� ���������� �� ����� ������� ��������� ��� �������
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_goodmarket.setsupply((i->second).getprice(), (i->second).getstock(), i->first);
	}
	//������������� �������� ������ �� ������������
	for (int i = 0; i < households.size(); i++)
	{
		households[i].buygoods(_goodmarket.getdemand());
	}
	//����� �������� ���������� �������
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).getsales(_goodmarket.getsales(i->first));
	}
}






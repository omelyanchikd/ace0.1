#include "world.h"


world::world(void)
{
}

world::world(int firmnumber, int householdnumber, double firmmoney, double householdmoney)
{
	firms.clear();
	households.clear();
	for (int i = 0; i < firmnumber; i++)
	{
		firms.push_back(firm(i+1, firmmoney));
	}
	for (int i = 0; i < householdnumber; i++)
	{
		households.push_back(household(i+1, householdmoney));
	}
	goodsupply.clear();
	gooddemand.clear();
	goodsupplyinfo.clear();

	_labordemand.clear();
	_laborsupply.clear();
	_invitations.clear();
}

void world::step()
{
	goodsupply.clear();
	gooddemand.clear();
	goodsupplyinfo.clear();
	for (int iter = 0; iter < 2; iter++)
	{
		_labordemand.clear();
		_laborsupply.clear();
		_invitations.clear();
		//����� ��������� �������� �� ����� �����
		for (int i = 0; i < firms.size(); i++)
		{
			_labormarket.setvacancies(firms[i].postvacancy());	
		}
		_laborsupply.resize(_labordemand.size());
		_invitations.resize(households.size());
		//������������� ������������� �������� ����� ������� � ��������, ���� ����������
		for (int i = 0; i < households.size(); i++)
		{
			_labormarket.setresumes(households[i].searchwork(_labormarket.getvacancies()), households[i].getid());
		}
		//����� ������������� ������ ���������� � ���������� �� ������ ������������� �����������
		for (int i = 0; i < firms.size(); i++)
		{
			sortinvites(firms[i].checkresumes(_laborsupply[i]), firms[i].getid());
		}
		//������������� �������� ����������� ������ � �������� ������������, � ����� �������� �� ������ �������������, ��������� �� �����������
		for (int i = 0; i < households.size(); i++)
		{
			firms[households[i].chooseemployee(_invitations[i])-1].hire(households[i].getid());
		}
	}
	//����� ���������� ���������
	for (int i = 0; i < firms.size(); i++)
	{
		firms[i].produce();
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
	for (int i = 0; i < firms.size(); i++)
	{
		goodsupply.push_back(firms[i].postoffer());
	}
	goodsupplyinfo = duplicate<offer>(goodsupply);
	//������������� �������� ������ �� ������������
	for (int i = 0; i < households.size(); i++)
	{
		households[i].buygoods(goodsupply);
	}
	//����� �������� ���������� �������
	for (int i = 0; i < firms.size(); i++)
	{
		firms[i].getsales(sales(firms[i].getid()));
	}
}

//������� ������� �������� �� ������ �. ��������� ���� ���������� � 1, � �� � 0 �. ������� ������ � ������� ����������� ����� �� ��������� � �������� ��������� ����
void world::sortresumes(vector<int> resumes, int householdid)
{
	for (int i = 0; i < resumes.size(); i++)
	{
		_laborsupply[resumes[i]-1].push_back(householdid);
	}
}

//������� ������� ��������
void world::sortinvites(vector<int> invites, int firmid)
{
	for (int i = 0; i < invites.size(); i++)
	{
		_invitations[invites[i]].push_back(_labordemand[findmatch(firmid, _labordemand)]);
	}
}

double world::sales(int firmid)
{
	double stock = getcount(firmid, goodsupplyinfo);
	double unsold = getcount(firmid, goodsupply);
//	double price = getprice(firmid, goodsupplyinfo);
	return (stock - unsold);
}


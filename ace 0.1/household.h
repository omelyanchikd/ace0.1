#pragma once

#include <vector>
#include <map>
#include <iostream>

#include "stdlib.h"

#include "offer.h"

#include "service.h"

using namespace std;

class household
{
public:
	//������������ ������
	household(void);
	household(double money);
	//���������� �� ����� �����
	vector<int> searchwork(map<int, double> labordemand);
	int chooseemployee(vector<int> proposals, map<int, double> labordemand);
	//��������� ������

	/*������*/
	void work(); 
	void quit();

	/*������� �� �����������*/
	void gethelp();

	//���������� �� ����� �������
	double consumptionbudget();
	void buygoods(vector<offer> &supply);
	void buy(offer& good, double& available, double& spent);
	//������ � ������� ����������
	bool isemployed();
	int getemployee();
	double getsalary();
	double getmoney();
	double getreservation();
	double getconsumption();
	void printinfo();


private:
	//������� �������
	double _salary;
	bool _employed;
	bool _active;
	int _employee;
	//���������� ����������
	double _money;
	double _reservation_wage;
	double _consumption_budget;
};


#pragma once

#include <vector>

#include "stdlib.h"

#include "vacancy.h"
#include "offer.h"

#include "service.h"

using namespace std;

class household
{
public:
	//������������ ������
	household(void);
	household(int id, double money);
	//���������� �� ����� �����
	vector<int> searchwork(vector<vacancy> labordemand);
	int chooseemployee(vector<vacancy> proposals);
	//��������� ������

	/*������*/
	void work(); 

	/*������� �� �����������*/
	void gethelp();

	//���������� �� ����� �������
	double consumptionbudget();
	void buygoods(vector<offer> goodsupply);
	void buy(offer good, double& available, double& spent);
	//������ � ������� ����������
	bool isemployed();
	int getid();

private:
	//������������� ������
	int _id;
	//������� �������
	double _salary;
	bool _employed;
	int _employee;
	//���������� ����������
	double _money;
	double _reservation_wage;
	double _consumption_budget;
};


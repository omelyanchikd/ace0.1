#pragma once

#include <vector>
#include <map>
#include <iostream>

#include "stdlib.h"

#include "offer.h"

using namespace std;

class household
{
public:
	//Конструкторы агента
	household(void);
	household(double money);
	//Активность на рынке труда
	vector<int> searchwork(map<int, double> labordemand);
	int chooseemployee(vector<int> proposals, map<int, double> labordemand);
	//Получение дохода

	/*Работа*/
	void work(); 
	void quit();

	/*Пособие по безработице*/
	void gethelp();

	//Активность на рынке товаров
	double consumptionbudget();
	void buy_goods(map<int, offer> &demand);
	void buy(offer& good, double& available, double& spent);
	//Доступ к частной информации
	bool is_employed();
	int get_employee();
	double getsalary();
	double getmoney();
	double getreservation();
	double getconsumption();
	int get_starve();
	int get_fed();
	void set_fed(int fed);
	void set_salary(double salary);
	void printinfo();


private:
	//Внешняя реакция
	double _salary;
	bool _employed;
	bool _active;
	int _employee;
	//Рассчетные показатели
	double _money;
	double _reservation_wage;
	double _consumption_budget;
	// Entry & exit parameters
	int _starve;
	int _fed;
};


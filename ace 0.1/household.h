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
	//Конструкторы агента
	household(void);
	household(int id, double money);
	//Активность на рынке труда
	vector<int> searchwork(vector<vacancy> labordemand);
	int chooseemployee(vector<vacancy> proposals);
	//Получение дохода

	/*Работа*/
	void work(); 

	/*Пособие по безработице*/
	void gethelp();

	//Активность на рынке товаров
	double consumptionbudget();
	void buygoods(vector<offer> goodsupply);
	void buy(offer good, double& available, double& spent);
	//Доступ к частной информации
	bool isemployed();
	int getid();

private:
	//Идентификатор агента
	int _id;
	//Внешняя реакция
	double _salary;
	bool _employed;
	int _employee;
	//Рассчетные показатели
	double _money;
	double _reservation_wage;
	double _consumption_budget;
};


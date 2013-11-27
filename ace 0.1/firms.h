#pragma once

#include <map>
#include <vector>
#include <fstream>

#include "firm.h"

#include "offer.h"

#include "scenario.h"

#include "data.h"

#include "rls.h"

using namespace std;

class firms
{
public:
	// Конструкторы.
	firms(void);
	firms(int n, double money, string model_name);
	// Рынок труда.
	map<int, double> set_vacancies();
	vector<int> fire();
	map<int, vector<int>> check_resumes(map<int, vector<int>> resumes);
	void hire(map <int, vector<int>> employers);
	// Производство.
	void produce();
	// Рынок товаров.
	map<int,offer> set_supply();
	void get_sales(map<int, int> sales);
	// Обучение.
	void learn(scenario _scenario);
	// Информация про окружающий мир.
	void set_info();
	// Вывод информации.
	void print_info();
	// Хранение информации.
	void write_log(data &_log);
	void write_log(string model_name);
	// Очистка.
	void clear();
	// Статистика.
	double production();
	double consumption();
	double average_price();
	double average_salary();
	double gdp();
//	double inflation();
	int firm_number();
	// Параметры обучения.
	double a();
	double b();
private:
	map<int, firm> _firms;
	rls _rls;
};


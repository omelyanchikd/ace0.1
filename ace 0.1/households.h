#pragma once

#include <vector>
#include <map>

#include "household.h"

#include "data.h"

using namespace std;

class households
{
public:
	// Конструкторы.
	households(void);
	households(int n, double money);
	// Рынок труда.
	map<int, vector<int>> search_work(map<int,double> vacancies);
	map<int, int> choose_employee(map<int, vector<int>> invites, map<int, double> vacancies);
	void quit(vector<int> fired);
	void update_salary(map<int, double> salaries);
	// Производство.
	void get_income();
	// Рынок товаров.
	void buy(map<int, offer> &demand);
	// Хранение информации.
	void write_log(data _log);
	// Вывод информации.
	void print_info();
	// Очистка.
	void clear();
	// Статистика.
	double unemployment();
private:
	map<int, household> _households;
};


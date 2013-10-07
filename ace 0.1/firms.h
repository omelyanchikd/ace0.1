#pragma once

#include <map>
#include <vector>

#include "firm.h"

#include "offer.h"

#include "data.h"

using namespace std;

class firms
{
public:
	// Конструкторы.
	firms(void);
	firms(int n, double money);
	// Рынок труда.
	map<int, double> set_vacancies();
	map<int, vector<int>> fire();
	map<int, vector<int>> check_resumes(map<int, vector<int>> resumes);
	void hire(map <int, int> employers);
	// Производство.
	void produce();
	// Рынок товаров.
	map<int,offer> set_supply();
	void get_sales(map<int, int> sales);
	// Обучение.
	void learn();
	// Вывод информации.
	void print_info();
	// Хранение информации.
	void write_log(data _log);
	// Очистка.
	void clear();
private:
	map<int, firm> _firms;
};


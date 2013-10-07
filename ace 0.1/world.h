#pragma once

#include "firms.h"
#include "households.h"

#include "labormarket.h"
#include "goodmarket.h"

#include "data.h"
#include "macro.h"

#include "offer.h"



#include <vector>
#include <map>

class world
{
public:
	
	world(void);
	world(int firmnuumber, int householdnumber, double firmmoney, double householdmoney);
	
	void step();

	void printinfo();

	data _log;
	macro _statistics;

private:

	firms _firms;
	households _households;
	
	labormarket _labormarket;
	goodmarket _goodmarket;
	
	void check_laborinfo();		// Проверка информации об изменении зарплаты и занятости.
	void get_statistics();		// Вычисление основных статистических показателей.
	void erase_vacancies();		// Очистить заполненные вакансии.
	void check_workers();		// Проверка уволившихся.
	// Статистика.
	double unemployment();		// Уровень безработицы.
	double production();		// Объем производства.
	double consumption();		// Объем потребления.
	double average_price();		// Средняя цена.
	double average_salary();	// Средняя заработная плата.
	double inflation();			// Инфляция.
	double gdp();				// Валовый внутренний продукт.

};


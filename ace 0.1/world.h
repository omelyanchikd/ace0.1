#pragma once

#include "firm.h"
#include "household.h"

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

	map<int, firm> firms;
	map<int, household> households;
	
	labormarket _labormarket;
	goodmarket _goodmarket;
	
	void set_vacancies();  		// Фирмы принимают решение об открытии вакансий на рынке труда или увольнении сотрудников.
	void set_resumes();	    	// Домохозяйства просматривают вакансии этого периода и выбирают, куда устроиться.
	void set_invites();	    	// Фирмы рассматривают списки кандидатов и приглашают на работу потенциальных сотрудников.
	void choose_employer();     // Домохозяйства получают предложения работы и выбирают работодателя, а фирмы нанимают на работу домохозяйства, принявшие их предложение.
	void produce();         	// Фирмы производят продукцию.
	void get_income();	        // Домохозяйства получают зарплату или пособие по безработице.
	void set_supply();			// Фирмы поставляют на рынок товаров продукцию для продажи.
	void buy();					// Домохозяйства выбирают товары из предложенных.
	void get_sales();			// Фирмы забирают полученную выручку.
	void firm_learning();		// Фирмы обновляют свои параметры по результатам итерации.
	void write_log();           // Временные ряды лога пополняются новыми значениями.
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


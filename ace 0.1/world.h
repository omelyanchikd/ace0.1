#pragma once

#include "firm.h"
#include "household.h"

#include "labormarket.h"
#include "goodmarket.h"

#include "data.h"

#include "offer.h"

#include "service.h"

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

private:

	map<int, firm> firms;
	map<int, household> households;
	
	labormarket _labormarket;
	goodmarket _goodmarket;
	
	void set_vacancies();  		// ‘ирмы открывают вакансии на рынке труда.
	void set_resumes();	    	// ƒомохоз€йства просматривают вакансии этого периода и выбирают, куда устроитьс€.
	void set_invites();	    	// ‘ирмы рассматривают списки кандидатов и приглашают на работу потенциальных сотрудников.
	void choose_employer();     // ƒомохоз€йства получают предложени€ работы и выбирают работодател€, а фирмы нанимают на работу домохоз€йства, прин€вшие их предложение.
	void produce();         	// ‘ирмы производ€т продукцию.
	void get_income();	        // ƒомохоз€йства получают зарплату или пособие по безработице.
	void set_supply();			// ‘ирмы поставл€ют на рынок товаров продукцию дл€ продажи.
	void buy();					// ƒомохоз€йства выбирают товары из предложенных.
	void get_sales();			// ‘ирмы забирают полученную выручку.
	void firm_learning();		// ‘ирмы обновл€ют свои параметры по результатам итерации.
	void write_log();           // ¬ременные р€ды лога пополн€ютс€ новыми значени€ми.

};


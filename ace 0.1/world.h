#pragma once

#include "firms.h"
#include "households.h"

#include "labormarket.h"
#include "goodmarket.h"

#include "data.h"
#include "macro.h"

#include "offer.h"

#include "scenario.h"

#include <vector>
#include <map>

class world
{
public:
	
	world(void);
	world(int firmnuumber, int householdnumber, double firmmoney, double householdmoney, scenario choice, string filename);
	
	void step();

	void printinfo();

	string _log;
//	data _log;
	macro _statistics;

private:

	firms _firms;
	households _households;
	
	labormarket _labormarket;
	goodmarket _goodmarket;

	scenario _scenario;
	
	void get_statistics();		// Вычисление основных статистических показателей.

};


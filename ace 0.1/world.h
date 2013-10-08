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
	
	void get_statistics();		// Вычисление основных статистических показателей.
};


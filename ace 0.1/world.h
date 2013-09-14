#pragma once

#include "firm.h"
#include "household.h"

#include "labormarket.h"
#include "goodmarket.h"

#include "offer.h"

#include "service.h"

#include <vector>
#include <map>

#include "agents.h"

class world
{
public:
	
	world(void);
	world(int firmnuumber, int householdnumber, double firmmoney, double householdmoney);
	void step();

private:

	map<int, firm> firms;
	vector<household> households;
	
	vector<offer> goodsupply;
	vector<double> gooddemand;
	vector<offer> goodsupplyinfo;

	labormarket _labormarket;
	goodmarket _goodmarket;

	double sales(int firmid);
};


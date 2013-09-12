#pragma once

#include "firm.h"
#include "household.h"

#include "labormarket.h"

#include "offer.h"
#include "vacancy.h"

#include "service.h"

#include <vector>

#include "agents.h"

class world
{
public:
	
	world(void);
	world(int firmnuumber, int householdnumber, double firmmoney, double householdmoney);
	void step();

private:

	vector<firm> firms;
	vector<household> households;
	
	vector<offer> goodsupply;
	vector<double> gooddemand;
	vector<offer> goodsupplyinfo;

	vector<vacancy> _labordemand;
	vector<vector<int>> _laborsupply;
	vector<vector<vacancy>> _invitations;  

	labormarket _labormarket;

	void sortinvites(vector<int> invites, int firmid);
	void sortresumes(vector<int> resumes, int householdid);

	double sales(int firmid);
};


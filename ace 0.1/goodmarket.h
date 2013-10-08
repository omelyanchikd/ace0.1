#pragma once

#include "offer.h"

#include <vector>
#include <map>

using namespace std;

class goodmarket
{
public:
	goodmarket(void);

	void set_supply(map<int, offer> supply);	

	map<int,int> get_sales();

	map<int, offer> _demand;

	void clear();

private:
	map<int, offer> _supply;

};


#pragma once

#include "offer.h"

#include <map>

using namespace std;

class goodmarket
{
public:
	goodmarket(void);

	void setsupply(int firmid, offer good);

private:
	map<int, offer> _supply;
	vector<offer> _goods;
};


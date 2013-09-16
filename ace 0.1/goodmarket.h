#pragma once

#include "offer.h"

#include <vector>

using namespace std;

class goodmarket
{
public:
	goodmarket(void);

	void setsupply(double price, double stock, int firmid);	

	vector<offer> _demand;

	double getsales(int firmid);

	void clear();



private:
	vector<offer> _supply;

};


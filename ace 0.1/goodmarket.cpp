#include "goodmarket.h"


goodmarket::goodmarket(void)
{
}

void goodmarket::setsupply(double price, double stock, int firmid)
{
	offer good(price, stock, firmid);
	_supply.push_back(good);
	_demand.push_back(good);
}

vector<offer> goodmarket::getdemand()
{
	return _demand;
}

double goodmarket::getsales(int firmid)
{
	double stock = getcount(firmid,_supply);
	double unsold = getcount(firmid, _demand);
	return (stock - unsold);
}

void goodmarket::clear()
{
	_supply.clear();
	_demand.clear();
}


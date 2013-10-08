#include "goodmarket.h"


goodmarket::goodmarket(void)
{
}

void goodmarket::set_supply(map<int, offer> supply)
{
	_supply = supply;
	_demand = supply;
}

map<int, int> goodmarket::get_sales()
{
	map<int, int> sales;
	for (map<int, offer>::iterator i = _supply.begin(); i != _supply.end(); ++i)
	{
		int stock = (i->second).get_count();
		int unsold = get_count(i->first, _demand);
		sales[i->first] = stock - unsold;
	}
	return sales;
}

void goodmarket::clear()
{
	_supply.clear();
	_demand.clear();
}


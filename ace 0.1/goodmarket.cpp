#include "goodmarket.h"


goodmarket::goodmarket(void)
{
}

void goodmarket::setsupply(int firmid, offer good)
{
	_supply[firmid] = good;
}


#include "macro.h"


macro::macro(void)
{
}

void macro::set_production(data log)
{
	double sum = 0;
	for (map<int, vector<double>>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice() * (i->second).getstock();
	}
}
	void set_consumption(data log);
	void set_unemployment(data log);
	void set_average_salary(data log);
	void set_average_price(data log);
	void set_all(data log);



#include "world.h"


world::world(void)
{
}

world::world(int firmnumber, int householdnumber, double firmmoney, double householdmoney)
{
	_firms = (firms(firmnumber, firmmoney));
	_households = (households(householdnumber, householdmoney));
	_goodmarket.clear();
	_labormarket.clear();
}

void world::step()
{
	_households.quit(_firms.fire());
	_households.update_salary(_firms.set_vacancies());
	for (int iter = 0; iter < 2; iter++)
	{
		_labormarket.set_vacancies(_firms.set_vacancies());
		_labormarket.set_resumes(_households.search_work(_labormarket.get_vacancies()));
		_labormarket.set_invites(_firms.check_resumes(_labormarket.get_resumes()));
		_firms.hire(_households.choose_employee(_labormarket.get_invites(), _labormarket.get_vacancies()));
		_labormarket.clear();
	}
	_firms.produce();
	_households.get_income();
	_goodmarket.set_supply(_firms.set_supply());
	_households.buy(_goodmarket._demand);
	_firms.get_sales(_goodmarket.get_sales());
	get_statistics();
	_firms.write_log(_log);
	_households.write_log(_log);
	_firms.print_info();
	_households.print_info();
	_firms.learn();
	_goodmarket.clear();
	_labormarket.clear();
}

/*double world::inflation()
{
	double sum = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice() * (i->second).getstock();
	}
	return sum/_statistics.inflation();
}//*/

void world::get_statistics()
{
	_statistics.set_unemployment(_households.unemployment());		// ”ровень безработицы.
	_statistics.set_production(_firms.production());			// ќбъем производства.
	_statistics.set_consumption(_firms.consumption());			// ќбъем потреблени€.
	_statistics.set_average_price(_firms.average_price());		// —редн€€ цена.
	_statistics.set_average_salary(_firms.average_salary());	// —редн€€ заработна€ плата.
	//_statistics.set_inflation(inflation());				// »нфл€ци€.
	_statistics.set_gdp(_firms.gdp());							// ¬аловый внутренний продукт.
}


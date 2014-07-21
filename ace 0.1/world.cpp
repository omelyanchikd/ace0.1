#include "world.h"


world::world(void)
{
}

world::world(int firmnumber, int householdnumber, double firmmoney, double householdmoney, scenario choice, string model_name, string rules_price, string rules_salary, string rules_plan)
{
	_raw = 1;
	_firms = (firms(firmnumber, firmmoney, model_name));
	_households = (households(householdnumber, householdmoney, model_name));
	_goodmarket.clear();
	_labormarket.clear();
	_scenario = choice;
	_model = model_name;
	ifstream fin;
	fin.open(rules_price);
	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		stringstream input(line);
		vector<double> values;
		while (!input.eof())
		{
			double val;
			input>>val;
			values.push_back(val);
		}
		_rules_price.push_back(values);
		values.clear();
		input.str("");
	}
	fin.close();
	fin.open(rules_salary);
	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		stringstream input(line);
		vector<double> values;
		while (!input.eof())
		{
			double val;
			input>>val;
			values.push_back(val);
		}
		_rules_salary.push_back(values);
		values.clear();
		input.str("");
	}
	fin.close();
    fin.open(rules_plan);
	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		stringstream input(line);
		vector<double> values;
		while (!input.eof())
		{
			double val;
			input>>val;
			values.push_back(val);
		}
		_rules_plan.push_back(values);
		values.clear();
		input.str("");
	}
	fin.close();
}

void world::step()
{
	_households.die();
	_households.birth();
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
	_firms.buy_raw(_raw);
	_firms.produce();
	_households.get_income();
	_goodmarket.set_supply(_firms.set_supply());
	_households.buy(_goodmarket._demand);
	_firms.get_sales(_goodmarket.get_sales());
	get_statistics();
	_firms.set_info();
	_firms.write_log(_model);
	_households.write_log(_model);
	_firms.print_info();
//	_households.print_info();
//	_firms.learn(_rules_price, _rules_salary, _rules_plan);
	_firms.learn(_scenario);
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
	_statistics.set_unemployment(_households.unemployment());		// Уровень безработицы.
	_statistics.set_production(_firms.production());			// Объем производства.
	_statistics.set_consumption(_firms.consumption());			// Объем потребления.
	_statistics.set_average_price(_firms.average_price());		// Средняя цена.
	_statistics.set_average_salary(_firms.average_salary());	// Средняя заработная плата.
	//_statistics.set_inflation(inflation());				// Инфляция.
	_statistics.set_gdp(_firms.gdp());							// Валовый внутренний продукт.
	_statistics.set_firm(_firms.firm_number());					// Количество фирм.
	_statistics.set_household(_households.household_number());	// Количество домохозяйств.
}


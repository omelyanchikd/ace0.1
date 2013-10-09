#include "macro.h"


macro::macro(void)
{
/*	_inflation.push_back(1);
	_unemployment_rate.push_back(0);
	_gdp.push_back(0);
	_consumption.push_back(0);
	_average_salary.push_back(0);
	_average_price.push_back(0);
	_production.push_back(0);//*/
}

double macro::inflation()
{
	return _inflation[_inflation.size()-1];
}

void macro::set_production(double production)
{
	_production.push_back(production);
}

void macro::set_consumption(double consumption)
{
	_consumption.push_back(consumption);
}

void macro::set_unemployment(double unemployment)
{
	_unemployment_rate.push_back(unemployment);
}

void macro::set_average_salary(double salary)
{
	_average_salary.push_back(salary);
}

void macro::set_average_price(double price)
{
	_average_price.push_back(price);
}

void macro::set_inflation(double inflation)
{
	_inflation.push_back(inflation);
}

void macro::set_gdp(double gdp)
{
	_gdp.push_back(gdp);
}

void macro::set_firm(double firm_number)
{
	_firm_number.push_back(firm_number);
}

void macro::set_household(double household_number)
{
	_household_number.push_back(household_number);
}

vector<double> macro::get_production()
{
	return _production;
}

vector<double> macro::get_consumption()
{
	return _consumption;
}

vector<double> macro::get_unemployment()
{
	return _unemployment_rate;
}

vector<double> macro::get_average_salary()
{
	return _average_salary;
}

vector<double> macro::get_average_price()
{
	return _average_price;
}
	
vector<double> macro::get_inflation()
{
	return _inflation;
}

vector<double> macro::get_gdp()
{
	return _gdp;
}

vector<double> macro::get_firm()
{
	return _firm_number;
}

vector<double> macro::get_household()
{
	return _household_number;
}
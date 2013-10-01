#pragma once

#include <vector>

#include "data.h"

using namespace std;

class macro
{
public:
	macro(void);
//-------------------------------------
	void set_production(data log);
	void set_consumption(data log);
	void set_unemployment(data log);
	void set_average_salary(data log);
	void set_average_price(data log);
	void set_all(data log);
//-------------------------------------
	double get_production();
	double get_consumption();
	double get_unemployment();
	double get_average_salary();
	double get_average_price();


private:
	vector<double> _inflation;
	vector<double> _unemployment_rate;
	vector<double> _gdp;
	vector<double> _consumption;
	vector<double> _average_salary;
	vector<double> _average_price;
	vector<double> _production;
};


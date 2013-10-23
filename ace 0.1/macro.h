#pragma once

#include <vector>

using namespace std;

class macro
{
public:
	macro(void);
//-------------------------------------
	void set_production(double production);
	void set_consumption(double consumption);
	void set_unemployment(double unemployment);
	void set_average_salary(double salary);
	void set_average_price(double price);
	void set_inflation(double inflation);
	void set_gdp(double gdp);
	void set_firm(double firm_number);
	void set_household(double household_number);
	//void set_all();
//-------------------------------------
	vector<double> get_production();
	vector<double> get_consumption();
	vector<double> get_unemployment();
	vector<double> get_average_salary();
	vector<double> get_average_price();
	vector<double> get_inflation();
	vector<double> get_gdp();
	vector<double> get_firm();
	vector<double> get_household();
//-------------------------------------
	double inflation();


private:
	vector<double> _inflation;
	vector<double> _unemployment_rate;
	vector<double> _gdp;
	vector<double> _consumption;
	vector<double> _average_salary;
	vector<double> _average_price;
	vector<double> _production;
	vector<double> _firm_number;
	vector<double> _household_number;
};


#pragma once

#include <vector>
#include <map>

using namespace std;

class log
{
public:
	log(void);
private:
	//∆урнал фирм
	vector<map<int,double>> _firm_salary;
	vector<map<int,double>> _firm_price;
	vector<map<int,double>> _firm_sold;
	vector<map<int,double>> _firm_workers;
	vector<map<int,double>> _firm_money;
	vector<map<int,double>> _firm_profit;
	vector<map<int,double>> _firm_desired;
	vector<map<int,double>> _firm_stock;
	//∆урнал домохоз€йств
	vector<map<int,double>> _household_salary;
	vector<map<int,double>> _household_employed;
	vector<map<int,double>> _household_employee;
	vector<map<int,double>> _household_money;
	vector<map<int,double>> _household_reservation;
	vector<map<int,double>> _household_consumptiom;
};


#include "data.h"


data::data(void)
{
	_firm_salary.clear();
	_firm_price.clear();
	_firm_sold.clear();
	_firm_workers.clear();
	_firm_money.clear();
	_firm_profit.clear();
	_firm_desired.clear();
	_firm_stock.clear();
	_household_salary.clear();
	_household_employed.clear();
	_household_employee.clear();
	_household_money.clear();
	_household_reservation.clear();
	_household_consumption.clear();
}

void data::setfirmsalary(int firmid, double salary)
{
	_firm_salary[firmid].push_back(salary);
}

void data::setfirmprice(int firmid, double price)
{
	_firm_price[firmid].push_back(price);
}

void data::setfirmsold(int firmid, double sold)
{
	_firm_sold[firmid].push_back(sold);
}

void data::setfirmworkers(int firmid, int workers)
{
	_firm_workers[firmid].push_back(workers);
}

void data::setfirmmoney(int firmid, double money)
{
	_firm_money[firmid].push_back(money);
}

void data::setfirmsprofit(int firmid, double profit)
{
	_firm_profit[firmid].push_back(profit);
}

void data::setfirmdesired(int firmid, int desired)
{
	_firm_desired[firmid].push_back(desired);
}

void data::setfirmstock(int firmid, double stock)
{
	_firm_stock[firmid].push_back(stock);
}

void data::sethouseholdsalary(int householdid, double salary)
{
	_household_salary[householdid].push_back(salary);
}

void data::sethouseholdemployed(int householdid, bool employed)
{
	_household_employed[householdid].push_back(employed);
}

void data::sethouseholdemployee(int householdid, int employee)
{
	_household_employee[householdid].push_back(employee);
}

void data::sethouseholdmoney(int householdid, double money)
{
	_household_money[householdid].push_back(money);
}

void data::sethouseholdreservation(int householdid, double reservation)
{
	_household_reservation[householdid].push_back(reservation);
}

void data::sethouseholdconsumption(int householdid, double consumption)
{
	_household_consumption[householdid].push_back(consumption);
}

void data::printinfo()
{
	for (map<int, vector<double>>::iterator i = _firm_salary.begin(); i != _firm_salary.end(); i++)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
}

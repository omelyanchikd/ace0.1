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

void data::setfirmworkers(int firmid, double workers)
{
	_firm_workers[firmid].push_back(workers);
}

void data::setfirmmoney(int firmid, double money)
{
	_firm_money[firmid].push_back(money);
}

void data::setfirmprofit(int firmid, double profit)
{
	_firm_profit[firmid].push_back(profit);
}

void data::setfirmdesired(int firmid, double desired)
{
	_firm_desired[firmid].push_back(desired);
}

void data::setfirmstock(int firmid, double stock)
{
	_firm_stock[firmid].push_back(stock);
}

void data::setfirmaction(int firmid, double action)
{
	_firm_action[firmid].push_back(action);
}

void data::sethouseholdsalary(int householdid, double salary)
{
	_household_salary[householdid].push_back(salary);
}

void data::sethouseholdemployed(int householdid, bool employed)
{
	_household_employed[householdid].push_back(employed);
}

void data::sethouseholdemployee(int householdid, double employee)
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

map<int,vector<double>> data::getfirmsalary()
{
	return _firm_salary;
}

map<int, vector<double>> data::getfirmprice()
{
	return _firm_price;
}


map<int, vector<double>> data::getfirmsold()
{
	return _firm_sold;
}

map<int, vector<double>> data::getfirmworkers()
{
	return _firm_workers;
}

map<int, vector<double>> data::getfirmmoney()
{
	return _firm_money;
}

map<int, vector<double>> data::getfirmprofit()
{
	return _firm_profit;
}

map<int, vector<double>> data::getfirmdesired()
{
	return _firm_desired;
}

map<int, vector<double>> data::getfirmstock()
{
	return _firm_stock;
}

map<int, vector<double>> data::getfirmaction()
{
	return _firm_action;
}

void data::printinfo()
{
	cout<<"Salary"<<endl;
	for (map<int, vector<double>>::iterator i = _firm_salary.begin(); i != _firm_salary.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Price"<<endl;
	for (map<int, vector<double>>::iterator i = _firm_price.begin(); i != _firm_price.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Sold"<<endl;
	for (map<int, vector<double>>::iterator i = _firm_sold.begin(); i != _firm_sold.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Workers"<<endl;
	for (map<int, vector<double>>::iterator i = _firm_workers.begin(); i != _firm_workers.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Money"<<endl;
	for (map<int, vector<double>>::iterator i = _firm_money.begin(); i != _firm_money.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Profit"<<endl;
	for (map<int, vector<double>>::iterator i = _firm_profit.begin(); i != _firm_profit.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Desired workers"<<endl;
	for (map<int, vector<double>>::iterator i = _firm_desired.begin(); i != _firm_desired.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Stock"<<endl;
	for (map<int, vector<double>>::iterator i = _firm_stock.begin(); i != _firm_stock.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Money"<<endl;
	for (map<int, vector<double>>::iterator i = _firm_money.begin(); i != _firm_money.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Salary"<<endl;
	for (map<int, vector<double>>::iterator i = _household_salary.begin(); i != _household_salary.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Employed"<<endl;
	for (map<int, vector<bool>>::iterator i = _household_employed.begin(); i != _household_employed.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Employee"<<endl;
	for (map<int, vector<double>>::iterator i = _household_employee.begin(); i != _household_employee.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Money"<<endl;
	for (map<int, vector<double>>::iterator i = _household_money.begin(); i != _household_money.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Reservation wage"<<endl;
	for (map<int, vector<double>>::iterator i = _household_reservation.begin(); i != _household_reservation.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}
	cout<<"Consumption budget"<<endl;
	for (map<int, vector<double>>::iterator i = _household_consumption.begin(); i != _household_consumption.end(); ++i)
	{
		cout<<"Firm id: "<<i->first<<endl;
		for (int time = 0; time < (i->second).size(); time++)
		{
			cout<<(i->second)[time]<<" ";
		}
		cout<<endl;
	}	
}

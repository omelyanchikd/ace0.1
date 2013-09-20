#pragma once

#include <vector>
#include <map>
#include <iostream>

using namespace std;

class data
{
public:
	data(void);

	void setfirmsalary(int firmid, double salary);
	void setfirmprice(int firmid, double price);
	void setfirmsold(int firmid, double sold);
	void setfirmworkers(int firmid, int workers);
	void setfirmmoney(int firmid, double money);
	void setfirmprofit(int firmid, double profit);
	void setfirmdesired(int firmid, int desired);
	void setfirmstock(int firmid, double stock);	

	void sethouseholdsalary(int householdid, double salary);
	void sethouseholdemployed(int householdid, bool employed);
	void sethouseholdemployee(int householdid, int employee);
	void sethouseholdmoney(int householdid, double money);
	void sethouseholdreservation(int householdid, double reservation);
	void sethouseholdconsumption(int householdid, double consumption);

	map<int,vector<double>> getfirmsalary();
	map<int, vector<double>> getfirmprice();
	map<int, vector<double>> getfirmsold();
	map<int, vector<int>> getfirmworkers();
	map<int, vector<double>> getfirmmoney();
	map<int, vector<double>> getfirmprofit();
	map<int, vector<int>> getfirmdesired();
	map<int, vector<double>> getfirmstock();	

	void printinfo();
private:
	//∆урнал фирм
	map<int,vector<double>> _firm_salary;
	map<int,vector<double>> _firm_price;
	map<int,vector<double>> _firm_sold;
	map<int,vector<int>> _firm_workers;
	map<int,vector<double>> _firm_money;
	map<int,vector<double>> _firm_profit;
	map<int,vector<int>> _firm_desired;
	map<int,vector<double>> _firm_stock;
	//∆урнал домохоз€йств
	map<int,vector<double>> _household_salary;
	map<int,vector<bool>> _household_employed;
	map<int,vector<int>> _household_employee;
	map<int,vector<double>> _household_money;
	map<int,vector<double>> _household_reservation;
	map<int,vector<double>> _household_consumption;
};


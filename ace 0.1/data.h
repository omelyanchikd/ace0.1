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
	void setfirmsprofit(int firmid, double profit);
	void setfirmdesired(int firmid, int desired);
	void setfirmstock(int firmid, double stock);	

	void sethouseholdsalary(int householdid, double salary);
	void sethouseholdemployed(int householdid, bool employed);
	void sethouseholdemployee(int householdid, int employee);
	void sethouseholdmoney(int householdid, double money);
	void sethouseholdreservation(int householdid, double reservation);
	void sethouseholdconsumption(int householdid, double consumption);

	void printinfo();
private:
	//������ ����
	map<int,vector<double>> _firm_salary;
	map<int,vector<double>> _firm_price;
	map<int,vector<double>> _firm_sold;
	map<int,vector<int>> _firm_workers;
	map<int,vector<double>> _firm_money;
	map<int,vector<double>> _firm_profit;
	map<int,vector<int>> _firm_desired;
	map<int,vector<double>> _firm_stock;
	//������ ������������
	map<int,vector<double>> _household_salary;
	map<int,vector<double>> _household_employed;
	map<int,vector<double>> _household_employee;
	map<int,vector<double>> _household_money;
	map<int,vector<double>> _household_reservation;
	map<int,vector<double>> _household_consumption;
};


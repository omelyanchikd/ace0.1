#pragma once

#include <vector>
#include <iostream>

#include "stdlib.h"

#include "offer.h"
#include "service.h"

using namespace std;

class firm 
{

public:

	//-----Constructor-----//
	firm(void);
	firm (double money);
	//-----Labor-market-----//
	vector<int> checkresumes(vector<int> resumes);         //Check income resumes and select appropriate candidates   
	void hire(int id);                 //Hire final candidates 
	void hire(vector<int> ids);
	//-----Good-market-----//
	void getsales(double sold);//, int buyers);             //Get money from sales   
	//-----Production-----//
	void produce();
	//Доступ к частной информации
	double getstock();
	double getprice();
	double getsalary();
	double getsold();
	int getworkers();
	double getmoney();
	double getprofit();
	int getdesired();
	void printinfo();

private:

	//-----Exogenous-parameters-----//
	double _elasticity; 
	double _productivity;
	//-----Parameters-----//
	double _price;
	double _salary;
	double _plan;
	//-----Reaction-----//
	double _sold;
	vector <int> _workers_ids;
	int _workers;
	int _resume_number;
//	int _buyers;
	//-----Calculations-----//
	double _money;
	double _profit;
	int _desired_workers;
	double _stock;
};



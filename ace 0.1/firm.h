#pragma once

#include <vector>
#include <iostream>

#include "stdlib.h"

#include "offer.h"
#include "unconscious.h"

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
	vector<int> fire();				   // Fire extra workers.
	void fire(int id);
	//-----Good-market-----//
	void getsales(int sold);//, int buyers);             //Get money from sales   
	//-----Production-----//
	void produce();
	//Доступ к частной информации
	int getstock();
	double getprice();
	double getsalary();
	int getsold();
	int getworkers();
	vector<int> getworkerids();
	double getmoney();
	double getprofit();
	int getdesired();
	void printinfo();
	// Обучение и изменение основных параметров.
	void learn();
	void set_salary();
	void set_price();
	void set_desired();

private:

	//-----Exogenous-parameters-----//
	double _elasticity; 
	double _productivity;
	//-----Parameters-----//
	double _price;
	double _salary;
	double _plan;
	//-----Reaction-----//
	int _sold;
	vector <int> _workers_ids;
	int _resume_number;
//	int _buyers;
	//-----Calculations-----//
	double _money;
	double _profit;
	int _desired_workers;
	int _stock;
	//---Learning parameters---
	unconscious _learning;
	double price_change;
	double salary_change;
	double desired_change;

};



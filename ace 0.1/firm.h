#pragma once

#include <vector>
#include <iostream>

#include "stdlib.h"

#include "offer.h"

#include "scenario.h"

#include "unconscious.h"
#include "qlearning.h"

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
	double getaction();
	void printinfo();
	// Обучение и изменение основных параметров.
	void learn(scenario choice);
	void set_salary(scenario choice);
	void set_price(scenario choice);
	void set_desired(scenario choice);
	void set_parameters(scenario choice);
	void set_info(double a, double b, int f);

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
	int _action;
	double price_change;
	double salary_change;
	double desired_change;
	double price_base;
	double salary_base;
	double desired_base;
	double price_alpha;
	double salary_alpha;
	double desired_alpha;
	double _a;
	double _b;
	int _f;
	// Unconscious learning.
	unconscious _unconscious_learning;
	// Q-learning.
	qlearning _qlearning;
	int get_state();
	// Intuitive.
	vector<double> _sales;
	int t;
	int period;
	double sum_sales();
	

};



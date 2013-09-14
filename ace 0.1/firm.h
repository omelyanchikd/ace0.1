#pragma once

#include <vector>

#include "agents.h"
#include "stdlib.h"

#include "vacancy.h"
#include "offer.h"
#include "service.h"

using namespace std;

class firm 
{

public:

	//-----Constructor-----//
	firm(void);
	firm (int id, double money);
	//-----Labor-market-----//
	vacancy postvacancy();          //Open vacancy at the local labor market
	vector<int> checkresumes(vector<int> resumes);         //Check income resumes and select appropriate candidates   
	void hire(int id);                 //Hire final candidates 
	void hire(vector<int> ids);
	//-----Good-market-----//
	offer postoffer();            //Post offer of goods at the global good market
	void getsales(double sold);//, int buyers);             //Get money from sales   
	//-----Production-----//
	void produce();
	//Доступ к приватной информации
	int getid();

private:

	//-----Identifier-----//
	int _id;
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
	int _buyers;
	//-----Calculations-----//
	double _money;
	double _profit;
	int _desired_workers;
	double _stock;
};



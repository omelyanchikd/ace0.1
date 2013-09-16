#include "firm.h"


firm::firm(void)
{
	//-----Exogenous parameters-----//
	_elasticity = 0; 
	_productivity = 0;
	//-----Parameters-----//
	_price = 0;
	_salary = 0;
	_plan = 0;
	//-----Reaction-----//
	_sold = 0;
	_workers = 0;
	_resume_number = 0;
	_buyers = 0;
	//-----Calculations-----//
	_money = 0;
	_profit = 0;
	_desired_workers = 0;
}

firm::firm(double money)
{
	//-----Exogenous parameters-----//
	_elasticity = -1.5; 
	_productivity = 2;
	//-----Parameters-----//
	_price = 0.5;
	_salary = 1.5;
	_plan = 0;
	//-----Reaction-----//
	_sold = 0;
	_workers = 0;
	_resume_number = 0;
	_buyers = 0;
	//-----Calculations-----//
	_money = money;
	_profit = 0;
	_desired_workers = 5;
}

double firm::postvacancy()
{
	return _salary;
}

vector<int> firm::checkresumes(vector<int> resumes)
{
   _resume_number = resumes.size();
   vector <int> invite;
   if (_desired_workers > _workers)
   {
	   if (resumes.size() == 0)
          return resumes;
       do
       {
           int j = rand()/(double)RAND_MAX * resumes.size();
           if (!isin<int>(invite, j))
           {
               invite.push_back(j);
           }
       }
       while ((invite.size() < resumes.size() && (invite.size() < _desired_workers - _workers)));
   }
   return invite;
}

void firm::hire(vector<int> ids)
{
	_workers += ids.size();
	for (int i = 0; i < ids.size(); i++)
	{
		_workers_ids.push_back(ids[i]);
	}
}

void firm::hire(int id)
{
	_workers++;
    _workers_ids.push_back(id);	
}

void firm::getsales(double sold)//, int buyers)
{
	_sold = sold;
//	_buyers = buyers;
	_money += _price * _sold;
}

void firm::produce()
{
	_stock = _productivity * _workers;
	_money -= _salary * _workers;
}

double firm::getstock()
{
	return _stock;
}

double firm::getprice()
{
	return _price;
}

void firm::printinfo()
{
	cout<<"Price: "<<_price;
	cout<<"Salary: "<<_salary;	
	cout<<"Sold: "<<_sold;
	cout<<"Workers: ";
	for (int i = 0; i < _workers_ids.size(); i++)
	{
		cout<<_workers_ids[i];
	}
	cout<<"Number of workers: "<<_workers;
	cout<<"Number of income resumes: "<<_resume_number;
	cout<<"Money: "<<_money;
	cout<<"Profit: "<<_profit;
	cout<<"Desired workers: "<<_desired_workers;
	cout<<"Stock: "<<_stock;
}
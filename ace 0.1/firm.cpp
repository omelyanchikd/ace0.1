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
//	_buyers = 0;
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
//	_buyers = 0;
	//-----Calculations-----//
	_money = money;
	_profit = 0;
	_desired_workers = 5;
}

vector<int> firm::checkresumes(vector<int> resumes)
{
   _workers_ids.clear();
   _resume_number = resumes.size();
   vector <int> invite;
   if (_desired_workers > _workers)
   {
	   if (resumes.size() == 0)
          return resumes;
       do
       {
           int j = rand()/(double)RAND_MAX * resumes.size();		      
           invite.push_back(j);
           resumes.erase(resumes.begin() + j);
       }
       while ((invite.size() < resumes.size() && (invite.size() < _desired_workers - _workers)));
   }
   return invite;
}

void firm::hire(vector<int> ids)
{
	_workers = ids.size();
	for (int i = 0; i < ids.size(); i++)
	{
		_workers_ids.push_back(ids[i]);
	}
}

void firm::hire(int id)
{
	_workers_ids.push_back(id);	
}

void firm::getsales(double sold)//, int buyers)
{
	_sold = sold;
//	_buyers = buyers;
	_money += _price * _sold;
	_profit = _price * _sold - _salary * _workers;
}

void firm::produce()
{
	_workers = _workers_ids.size();
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

double firm::getsalary()
{
	return _salary;
}

double firm::getsold()
{
	return _sold;
}

int firm::getworkers()
{
	return _workers;
}

double firm::getmoney()
{
	return _money;
}

double firm::getprofit()
{
	return _profit;
}

int firm::getdesired()
{
	return _desired_workers;
}

void firm::printinfo()
{
	cout<<"Price: "<<_price<<endl;
	cout<<"Salary: "<<_salary<<endl;	
	cout<<"Sold: "<<_sold<<endl;
	cout<<"Workers: "<<endl;
	for (int i = 0; i < _workers_ids.size(); i++)
	{
		cout<<_workers_ids[i]<<endl;
	}
	cout<<"Number of workers: "<<_workers<<endl;
	cout<<"Number of income resumes: "<<_resume_number<<endl;
	cout<<"Money: "<<_money<<endl;
	cout<<"Profit: "<<_profit<<endl;
	cout<<"Desired workers: "<<_desired_workers<<endl;
	cout<<"Stock: "<<_stock<<endl;
}
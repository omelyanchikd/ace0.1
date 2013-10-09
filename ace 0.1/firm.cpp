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
	_resume_number = 0;
//	_buyers = 0;
	//-----Calculations-----//
	_money = 0;
	_profit = 0;
	_desired_workers = 0;
	_learning.init(27);
}

firm::firm(double money)
{
	//-----Exogenous parameters-----//
	_elasticity = -1.5; 
	_productivity = 2;
	//-----Parameters-----//
	_price = 1;
	_salary = 4;
	_plan = 0;
	//-----Reaction-----//
	_sold = 0;
	_resume_number = 0;
//	_buyers = 0;
	//-----Calculations-----//
	_money = money;
	_profit = 0;
	_desired_workers = 5;
	_learning.init(27);
}

vector<int> firm::checkresumes(vector<int> resumes)
{
//   _workers_ids.clear(); // Необходима проверка случая, когда домохозяйство решает уволиться из фирмы.
   _resume_number = resumes.size();
   vector <int> invite;
   if (_desired_workers > _workers_ids.size())
   {
	   if (resumes.size() == 0)
          return resumes;
       do
       {
           int j = rand()/(double)RAND_MAX * (resumes.size() - 1);		      
           invite.push_back(resumes[j]);
           resumes.erase(resumes.begin() + j);
       }
       while ((invite.size() < resumes.size() && (invite.size() < _desired_workers - _workers_ids.size())));
   }
   return invite;
}

void firm::hire(vector<int> ids)
{
	for (int i = 0; i < ids.size(); i++)
	{
		_workers_ids.push_back(ids[i]);
	}
}

void firm::hire(int id)
{
	_workers_ids.push_back(id);	
}

vector<int> firm::fire()
{
	vector<int> fired;	
	while (_workers_ids.size() > _desired_workers)
	{
           int j = rand()/(double)RAND_MAX * (_workers_ids.size() - 1);	
		   fired.push_back(_workers_ids[j]);
		   _workers_ids.erase(_workers_ids.begin() + j);		   
	}
	return fired;
}

void firm::getsales(int sold)//, int buyers)
{
	_sold = sold;
//	_buyers = buyers;
	_money += _price * _sold;
	_profit = _price * _sold - _salary * _workers_ids.size();
}

void firm::produce()
{
	_stock = _productivity * _workers_ids.size();
	_money -= _salary * _workers_ids.size();
}

int firm::getstock()
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

int firm::getsold()
{
	return _sold;
}

int firm::getworkers()
{
	return _workers_ids.size();
}

vector<int> firm::getworkerids()
{
	return _workers_ids;
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
	cout<<"Number of workers: "<<_workers_ids.size()<<endl;
	cout<<"Number of income resumes: "<<_resume_number<<endl;
	cout<<"Money: "<<_money<<endl;
	cout<<"Profit: "<<_profit<<endl;
	cout<<"Desired workers: "<<_desired_workers<<endl;
	cout<<"Stock: "<<_stock<<endl;
}

void firm::set_salary()
{
	switch (_learning.get_action() / 9)
	{
		case 2: _salary *= 0.8; break;
		case 1: _salary *= 1.2; break;
		case 0: break;
	}
}

void firm::set_price()
{
	switch ((_learning.get_action() / 3) % 3)
	{
		case 2: _price *= 0.8; break;
		case 1: _price *= 1.2; break;
		case 0: break;
	}
}

void firm::set_desired()
{
	switch ((_learning.get_action() % 9) % 3)
	{
		case 2: _desired_workers--; break;
		case 1: _desired_workers++; break;
		case 0: break;
	}

}

void firm::learn()
{
	_learning.update(_profit - 10);
	set_salary();
	set_price();
	set_desired();
}

void firm::fire(int id)
{
	for (int i = 0; i < _workers_ids.size(); i++)
	{
		if (_workers_ids[i] == id)
		{
			_workers_ids.erase(_workers_ids.begin() + i);
			break;
		}

	}
}
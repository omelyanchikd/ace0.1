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
	_unconscious_learning.init(27);
	_qlearning.init(6,27, 100);
	price_change = 1;
	salary_change = 1;
	desired_change = 1;
	price_base = 0;
	salary_base = 0;
	desired_base = 0;
	price_alpha = 0;
	salary_alpha = 0;
	desired_alpha = 0;
	_action = 0;
	_a = 0;
	_b = 0;
	_f = 0;
	t = 0;
	period = 0;
}

firm::firm(double money)
{
	//-----Exogenous parameters-----//
	_elasticity = -1.5; 
	_productivity = 3;
	//-----Parameters-----//
	_salary = 6;
	_plan = 0;
	_price = _salary/_productivity * ( 1 / (1 + 1 / _elasticity));
	//-----Reaction-----//
	_sold = 0;
	_resume_number = 0;
//	_buyers = 0;
	//-----Calculations-----//
	_money = money;
	_profit = 0;
	_desired_workers = 50;
	_unconscious_learning.init(27);
	_qlearning.init(6,27,100);
	price_change = 1;
	salary_change = 1;
	desired_change = 1;
	price_base = 1;
	salary_base = 4;
	desired_base = 50;
	price_alpha = 0.001;
	salary_alpha = 0.001;
	desired_alpha = 0.001;
	_action = 0;
	_a = 0;
	_b = 0;
	_f = 0;
	t = 3;
	period = 0;
	vector<double> fi;
	fi.push_back(104);
	fi.push_back(-1.0/3);
	_good = rls(fi, matrix(2));
	fi.clear();
	fi.push_back(14);
	fi.push_back(6);
	_labor = rls(fi, matrix(2));

}

vector<int> firm::checkresumes(vector<int> resumes)
{
   _resume_number = resumes.size();
   vector <int> invite;
   int _workers = _workers_ids.size();
   if (_desired_workers > _workers)
   {
	   if (resumes.size() == 0)
          return resumes;
       do
       {
           int j = rand()/(double)RAND_MAX * (resumes.size() - 1);		      
           invite.push_back(resumes[j]);
           resumes.erase(resumes.begin() + j);
       }
       while ((invite.size() < resumes.size()) && (invite.size() < _desired_workers - _workers));
   }
   _workers_ids.clear(); // Необходима проверка случая, когда домохозяйство решает уволиться из фирмы.
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

double firm::getaction()
{
	return _unconscious_learning.get_action();
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

void firm::set_salary(scenario choice)
{
	switch (choice.way)
	{
		case value:
					switch (_action / 9)
					{
						case 2: _salary *= 0.8; break;
						case 1: _salary *= 1.2; break;
						case 0: break;
					}
					break;
		case change:
					switch (_action / 9)
					{
						case 2: salary_change -= 0.1; break; 
						case 1: salary_change += 0.1; break; 
						case 0: break;
					}
					_salary *= salary_change;
					break;
		case share:
					switch (_action / 9)
					{
						case 2: salary_alpha -= 0.0005; break; 
						case 1: salary_alpha += 0.0005; break; 
						case 0: break;
					}
					_salary += salary_alpha * _profit;
					break;
	}
	if (_salary < 0)
		_salary = 0.001;
}

void firm::set_price(scenario choice)
{
	switch ((_unconscious_learning.get_action() / 3) % 3)
	{
		case 2: price_alpha -= 0.0005; break; //price_change -= 0.1; break; //_price *= 0.8; break;
		case 1: price_alpha += 0.0005; break;//price_change += 0.1; break; //_price *= 1.2; break;
		case 0: break;
	}
//	_price *= price_change;
//	_price = price_change * price_base;
	_price += price_alpha * _profit;
	if (_price < 0)
		_price = 0.001;
}

void firm::set_desired(scenario choice)
{
	switch ((_unconscious_learning.get_action() % 9) % 3)
	{
		case 2: desired_alpha -= 0.0005; break;//desired_change -= 0.1; break; //_desired_workers--; break;
		case 1: desired_alpha += 0.0005; break;//desired_change += 0.1; break; //_desired_workers++; break;
		case 0: break;
	}
//	_desired_workers = floor(desired_change * _desired_workers);
//	_desired_workers = floor(desired_change * desired_base);
	_desired_workers += floor(desired_alpha * _profit);

}

void firm::set_info(double a, double b, int f)
{
	_a = a;
	_b = b;
	_f = f;
}

void firm::set_parameters(scenario choice)
{
	switch (choice.parameters)
	{
		case salary_price_desired:
			switch (choice.way)
			{
				case value: 
						switch (_action / 9)
						{
							case 2: _salary *= 0.8; break;	
							case 1: _salary *= 1.2; break;
							case 0: break;
						}
						switch ((_action / 3) % 3)
						{
							case 2: _price *= 0.8; break;
							case 1: _price *= 1.2; break;
							case 0: break;
						}
						switch ((_action % 9) % 3)
						{
							case 2: _desired_workers--; break;
							case 1: _desired_workers++; break;
							case 0: break;
						}
						break;
				case change:
						switch (_action / 9)
						{
							case 2: salary_change -= 0.1; break; 
							case 1: salary_change += 0.1; break; 
							case 0: break;
						}
						switch ((_action / 3) % 3)
						{
							case 2: price_change -= 0.1; break;
							case 1: price_change += 0.1; break;
							case 0: break;
						}
						switch ((_action % 9) % 3)
						{
							case 2: desired_change -= 0.1; break;
							case 1: desired_change += 0.1; break;
							case 0: break;
						}
						_salary *= salary_change;
						_price *= price_change;
						_desired_workers = floor(desired_change * _desired_workers);
						break;
				case share:
						switch (_action / 9)
						{
							case 2: salary_alpha -= 0.0005; break; 
							case 1: salary_alpha += 0.0005; break; 
							case 0: break;
						}
						switch ((_action / 3) % 3)
						{
							case 2: price_change -= 0.1; break;
							case 1: price_change += 0.1; break;
							case 0: break;
						}
						switch ((_action % 9) % 3)
						{
							case 2: desired_change -= 0.1; break;
							case 1: desired_change += 0.1; break;
							case 0: break;
						}
						_salary += salary_alpha * _profit;
						_price += price_alpha * _profit;
						_desired_workers += floor(desired_alpha * _profit);
						break;
			}
			break;
		case salary_desired:
			switch (choice.way)
			{
				case value: 
						switch (_action / 3)
						{
							case 2: _salary *= 0.8; break;	
							case 1: _salary *= 1.2; break;
							case 0: break;
						}
						switch (_action % 3)
						{
							case 2: _desired_workers--; break;
							case 1: _desired_workers++; break;
							case 0: break;
						}
						_price = _salary/_productivity * ( 1 / (1 + 1 / _elasticity));						
						break;
				case change:
						switch (_action / 3)
						{
							case 2: salary_change -= 0.1; break; 
							case 1: salary_change += 0.1; break; 
							case 0: break;
						}
						switch (_action % 3)
						{
							case 2: desired_change -= 0.1; break;
							case 1: desired_change += 0.1; break;
							case 0: break;
						}
						_salary *= salary_change;						
						_desired_workers = floor(desired_change * _desired_workers);
						break;
				case share:
						switch (_action / 3)
						{
							case 2: salary_alpha -= 0.0005; break; 
							case 1: salary_alpha += 0.0005; break; 
							case 0: break;
						}
						switch (_action % 3)
						{
							case 2: desired_change -= 0.1; break;
							case 1: desired_change += 0.1; break;
							case 0: break;
						}
						_salary += salary_alpha * _profit;						
						_desired_workers += floor(desired_alpha * _profit);
						break;				
			}
			_price = _salary/_productivity * ( 1 / (1 + 1 / _elasticity));
			break;
	}
}

void firm::learn(scenario choice)
{
	double reward;
	switch (choice.criteria)
	{
		case profit:	  reward = _profit; break;
		case workers:	  reward = _workers_ids.size(); break;
		case return_rate: reward = _salary * _workers_ids.size() / _profit; break; 
//		case sales_change: reward =  
	}
	switch (choice.method)
	{
		case nonconscious: 
							_unconscious_learning.update(reward);
							_action = _unconscious_learning.get_action();
							set_parameters(choice);
							break;	
		case Qlearning:							
							_qlearning.update(get_state(), reward);
							_action = _qlearning.get_action();
							set_parameters(choice);
							break;
		case oligopoly:		
							if (_workers_ids.size() < _desired_workers)
								_salary *= 0.2;						
							_desired_workers = (_a - _salary/_productivity)/(_productivity * _b * (_f + 1));
							_price = (_a + _f * _salary/_productivity) / (_f + 1);
							break;
		case intuitive:		
							if (_workers_ids.size() < _desired_workers)
								_salary *= 1.05;
							if (period >= 3)
							{
								_desired_workers = (0.5 * _sold + 0.5 * sum_sales() / t)/ _productivity;
								_sales.erase(_sales.begin());
								_sales.push_back(_sold);
							}
							else
							{
								_sales.push_back(_sold);							
								period++;
							}
							_price = _salary/_productivity * ( 1 / (1 + 1 / _elasticity));
							break;
		case random:
							_salary = rand()/(double)RAND_MAX * 3 + 4;
							_desired_workers = rand()/(double)RAND_MAX * 20 + 50;
							_price = _salary/_productivity * ( 1 / (1 + 1 / _elasticity));
							break;
		case rational:
							vector<double> x;
							x.push_back(1);
							x.push_back(_sold);
							_good.update(_price, x);
							x.clear();
							x.push_back(1);
							x.push_back(_salary);
							_labor.update(_workers_ids.size(), x);
							vector<double> labor_action, good_action;
							labor_action = _labor.get_action();
							good_action = _good.get_action();
							double q = _productivity * (labor_action[0] + good_action[0] * labor_action[1] * _productivity) / (2 - 2 * good_action[1] * labor_action[1] * _productivity * _productivity);  
							_price = good_action[0] + good_action[1] * q;
							_desired_workers = q / _productivity;
							_salary = (q - _productivity * labor_action[0]) / (labor_action[1] * _productivity); 
	}			
//	set_salary(choice);
//	set_price(choice);
//	set_desired(choice);
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

int firm::get_state()
{
	if ((_sold == _stock) && (_workers_ids.size() == _desired_workers) && (_sold > 0))
		return 0;
	if ((_sold < _stock) && (_workers_ids.size() == _desired_workers) && (_sold > 0))
		return 1;
	if ((_sold == _stock) && (_workers_ids.size() < _desired_workers) && (_sold > 0))
		return 2;
	if ((_sold < _stock) && (_workers_ids.size() < _desired_workers) && (_sold > 0))
		return 3;
	if ((_sold == 0) && (_workers_ids.size() == 0))
		return 4;
	if ((_sold == 0) && (_workers_ids.size() > 0))
		return 5;
}

double firm::sum_sales()
{
	double sum = 0;
	for (int i = 0; i < _sales.size(); i++)
	{
		sum += _sales[i];
	}
	return sum;
}
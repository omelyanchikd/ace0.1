#include "firm.h"


firm::firm(void)
{
	//-----Exogenous parameters-----//
	_elasticity = 0; 
	_productivity = 0;
	_raw_need = 4;
	_raw_price = 0;
	//-----Parameters-----//
	_price = 0;
	_salary = 0;
	_plan = 0;
	//-----Reaction-----//
	_sold = 0;
	_resume_number = 0;
	_raw = 0;
//	_buyers = 0;

	//-----Calculations-----//
	_money = 0;
	_profit = 0;
	_desired_workers = 0;
	_unconscious_learning.init(100);
	_qlearning.init(6, 100, 100);
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
	_productivity = 5;
	_raw_need = 4;
	_raw_price = 0;
	//-----Parameters-----//
	_salary = 10;
	_plan = 0;
	_price = 5;//_salary/_productivity * ( 1 / (1 + 1 / _elasticity));
	//-----Reaction-----//
	_sold = 0;
	_resume_number = 0;
	_raw = 0;
//	_buyers = 0;
	//-----Calculations-----//
	_money = money;
	_profit = 0;
	_desired_workers = 100;
	_unconscious_learning.init(100);
	_qlearning.init(6,100,50);
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
	double p[4] = {1,2,3,4};
	fi.push_back(45);
	fi.push_back(1);
	_good = rls(fi, matrix(2,2,p));
	fi.clear();
	fi.push_back(10);
	fi.push_back(2);
	_labor = rls(fi, matrix(2,2,p));
	prev_sold = 0;//500;
	prev_profit = 0;//300;
	prev_workers = 0;//20;
}

void firm::buy_raw(double price)
{
	_raw_price = price;
	_money -= _raw_price * price * _productivity *_raw_need * _desired_workers;
	_raw = _productivity *_raw_need * _desired_workers;
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
	prev_workers = _workers_ids.size();
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
	prev_sold = _sold;
	_sold = sold;
//	_buyers = buyers;
	_money += _price * _sold;
	prev_profit = _profit;
	_profit = _price * _sold - _salary * _workers_ids.size() - _raw_price * _raw;
}

void firm::produce()
{
	_stock = _productivity * _workers_ids.size(); //sqrtf(_workers_ids.size());
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
/*						switch (_action / 9)
						{
//							case 4: _salary = 1; break; 
//							case 3: _salary = 2; break;
							case 2: _salary *= 0.8; break;	
							case 1: _salary *= 1.2; break;
							case 0: break; //_salary = 3; break;
						}
						switch ((_action / 3) % 3)
						{
							case 2: _price *= 0.8; break;
							case 1: _price *= 1.2; break;
							case 0: break;
						}//*/
/*						switch ((_action % 9) % 3)
						{
//							case 4: _desired_workers = 15; break;
//							case 3: _desired_workers = 25; break;
							case 2: _desired_workers--; break;
							case 1: _desired_workers++; break;
							case 0: break;//_desired_workers = 20; break;
						}//*/
						_salary = 3 + (_action - 50) / 100.0;
						_desired_workers = 30 + (_action - 50) / 10.0;
						_price = _salary/_productivity * ( 1 / (1 + 1 / _elasticity));	//*/
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
			_price = (_salary + _raw_price * _productivity * _raw_need)/_productivity * ( 1 / (1 + 1 / _elasticity));
			break;
	}
}

void firm::learn(scenario choice)
{ 
/*	set_salary(get_state_profit());
	set_price(get_state_sold());
	set_workers(get_state_workers());
	prev_profit = _profit;
	prev_sold = _sold;
	prev_workers = _workers_ids.size();//*/
	
	double reward;
	vector<double> x, labor_action, good_action;
	switch (choice.criteria)
	{
		case profit:	  reward = _profit - 100; break;
		case workers:	  reward = _workers_ids.size(); break;
		case return_rate: reward = _salary * _workers_ids.size() / _profit; break; 
		case forecast:	  reward = 0.333 * (_desired_workers -_workers_ids.size()) + 0.333 * (_stock - _sold) + 0.333 * (_profit);		 
//		case sales_change: reward =  
	}
	switch (choice.method)
	{
		case nonconscious: 
							_unconscious_learning.update(reward);
							_action = _unconscious_learning.get_action();
							set_parameters(choice);
							break;	
		case q_learning:							
							_qlearning.update(get_state(), reward);
							_action = _qlearning.get_action();
							set_parameters(choice);
							break;
		case oligopoly:		
							if (_workers_ids.size() < _desired_workers)
								_salary *= 1.05;						
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
							_desired_workers = rand()/(double)RAND_MAX * 50 + 50;
							_price = (_salary + _raw_price * _raw_need * _productivity)/_productivity * ( 1 / (1 + 1 / _elasticity));
							break;
		case rational_quantity:
							x.clear();
							x.push_back(1);
							x.push_back(_sold);
							_good.update(_price, x);
							x.clear();
							x.push_back(1);
							x.push_back(_salary);
							_labor.update(_workers_ids.size(), x);
							labor_action.clear();
							good_action.clear();
							labor_action = _labor.get_action();
							good_action = _good.get_action();
							_plan = _productivity * (labor_action[0] + good_action[0] * labor_action[1] * _productivity) / (2 - 2 * good_action[1] * labor_action[1] * _productivity * _productivity);  
							_price = good_action[0] + good_action[1] * _plan;
							_desired_workers = _plan / _productivity;
							_salary = (_desired_workers - labor_action[0]) / labor_action[1];
							break;
		case rational_salary:
							x.clear();				
							labor_action.clear();
							good_action.clear();
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
							_salary = (_productivity * good_action[0] * labor_action[1] + 2 * _productivity * _productivity * good_action[1] * labor_action[0] * labor_action[1] - 1) / (2 * labor_action[1] - 2 * _productivity * _productivity * good_action[1] * labor_action[1] * labor_action[1]); 
							_desired_workers = labor_action[0] + labor_action[1] * _salary; 
							_price = good_action[0] + good_action[1] * _productivity * _desired_workers;							
							break;
	}			
//	set_salary(choice);
//	set_price(choice);
//	set_desired(choice);//*/
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
	return 6;
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

void firm::write_log(string model_name, int firm_id)
{
	ofstream fout;
	ostringstream fn;
	fn<<model_name<<"_salary"<<"_firm_"<<firm_id<<".txt";
	fout.open(fn.str(), ios_base::app);
	fout<<_salary<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_price"<<"_firm_"<<firm_id<<".txt";
	fout.open(fn.str(), ios_base::app);
	fout<<_price<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_sold"<<"_firm_"<<firm_id<<".txt";
	fout.open(fn.str(), ios_base::app);
	fout<<_sold<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_workers"<<"_firm_"<<firm_id<<".txt";
	fout.open(fn.str(), ios_base::app);
	fout<<_workers_ids.size()<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_money"<<"_firm_"<<firm_id<<".txt";
	fout.open(fn.str(), ios_base::app);
	fout<<_money<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_profit"<<"_firm_"<<firm_id<<".txt";
	fout.open(fn.str(), ios_base::app);
	fout<<_profit<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_desired"<<"_firm_"<<firm_id<<".txt";
	fout.open(fn.str(), ios_base::app);
	fout<<_desired_workers<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_stock"<<"_firm_"<<firm_id<<".txt";
	fout.open(fn.str(), ios_base::app);
	fout<<_stock<<" ";
	fout.close();
	fn.str("");
}

int firm::get_state_profit()
{
	double change;
	if (prev_profit == 0)
		change = _profit * 100;
	else
		change = (_profit - prev_profit)/prev_profit * 100;
	if (change < - 100)
		return 0;
	if (change < - 50)
		return 1;
	if (change < - 20)
		return 2;
	if (change < - 10)
		return 3;
	if (change < - 5)
		return 4;
	if (change < 5)
		return 5;
	if (change < 10)
		return 6;
	if (change < 20)
		return 7;
	if (change < 50)
		return 8;
	if (change < 100)
		return 9;
	return 10;
}

int firm::get_state_sold()
{
	double change;
	if (prev_sold == 0)
		change = _sold * 100;
	else
		change = (_sold - prev_sold)/prev_sold * 100;
	if (change < - 100)
		return 0;
	if (change < - 50)
		return 1;
	if (change < - 20)
		return 2;
	if (change < - 10)
		return 3;
	if (change < - 5)
		return 4;
	if (change < 5)
		return 5;
	if (change < 10)
		return 6;
	if (change < 20)
		return 7;
	if (change < 50)
		return 8;
	if (change < 100)
		return 9;
	return 10;
}

int firm::get_state_workers()
{
	double change;
	if (prev_workers == 0)
		change = _workers_ids.size() * 100;
	else
		change = (_workers_ids.size() - prev_workers)/prev_workers * 100;
	if (change < - 100)
		return 0;
	if (change < - 50)
		return 1;
	if (change < - 20)
		return 2;
	if (change < - 10)
		return 3;
	if (change < - 5)
		return 4;
	if (change < 5)
		return 5;
	if (change < 10)
		return 6;
	if (change < 20)
		return 7;
	if (change < 50)
		return 8;
	if (change < 100)
		return 9;
	return 10;
}

void firm::set_price(int state)
{
	switch (state)
	{
		case 0:	_price *= 0,5; break;
		case 1: _price *= 0,6; break;
		case 2: _price *= 0,8; break;
		case 3: _price *= 0,9; break;
		case 4: _price *= 0,95; break;
		case 5: break;
		case 6: _price *= 1,05; break;
		case 7: _price *= 1,1; break;
		case 8: _price *= 1,2; break;
		case 9: _price *= 1,4; break;
		case 10: _price *= 1,5; break; 
	}	
}

void firm::set_salary(int state)
{
	switch (state)
	{
		case 0:	_salary *= 0,5; break;
		case 1: _salary *= 0,6; break;
		case 2: _salary *= 0,8; break;
		case 3: _salary *= 0,9; break;
		case 4: _salary *= 0,95; break;
		case 5: break;
		case 6: _salary *= 1,05; break;
		case 7: _salary *= 1,1; break;
		case 8: _salary *= 1,2; break;
		case 9: _salary *= 1,4; break;
		case 10: _salary *= 1,5; break; 
	}	
}

void firm::set_workers(int state)
{
	switch (state)
	{
		case 0:	_desired_workers *= 0,5; break;
		case 1: _desired_workers *= 0,6; break;
		case 2: _desired_workers *= 0,8; break;
		case 3: _desired_workers *= 0,9; break;
		case 4: _desired_workers *= 0,95; break;
		case 5: break;
		case 6: _desired_workers *= 1,05; break;
		case 7: _desired_workers *= 1,1; break;
		case 8: _desired_workers *= 1,2; break;
		case 9: _desired_workers *= 1,4; break;
		case 10: _desired_workers *= 1,5; break; 
	}	
}

void firm::learn(vector<vector<double>> rules_price, vector<vector<double>> rules_salary, vector<vector<double>> rules_plan)
{
	vector<double> state;
	if (prev_sold == 0)
		state.push_back(_sold * 100);
	else
		state.push_back((_sold - prev_sold)/prev_sold*100);
	if (prev_workers == 0)
		state.push_back(_workers_ids.size() * 100);
	else
		state.push_back((_workers_ids.size() - prev_workers)/prev_workers*100);
/*	if (prev_sold == 0)
		state.push_back(_sold);
	else
		state.push_back((_sold - prev_sold)/prev_sold*100);//*/
	_price *= (1 + set(state, rules_price)/100);
	_salary *= (1 + set(state, rules_salary)/100);
//	_desired_workers = _desired_workers * (1 + set(state, rules_plan)/100);
	if ((_profit < 0) && (prev_profit > 0))
		_desired_workers++;
	if ((_profit < 0) && (prev_profit < 0))
		_desired_workers--;
}

double firm::set(vector<double> state, vector<vector<double>> rules)
{
	for (int i = 0; i < rules.size(); i++)
	{
		int j = 0;
		for (j = 0; j < rules[i].size() - 2; j += 2)
		{
			if (!((rules[i][j] <= state[j/2]) && (state[j/2] < rules[i][j+1])))
				break;
		}
		if (j == rules.size() - 2)
			return (rules[i][j] + rand()/(double)RAND_MAX * (rules[i][j+1] - rules[i][j]));
	}
	int choice = rand() % rules.size();
	return (rules[choice][rules[choice].size()-2] + rand()/(double)RAND_MAX * (rules[choice][rules[choice].size()-1] - rules[choice][rules[choice].size()-2]));
}

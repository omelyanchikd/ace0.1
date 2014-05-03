#include "household.h"

household::household(void)
{
	//Реакция внешнего мира
	_salary = 0;
	_employed = false;
	_active = true;
	_employee = 0;
	//Рассчетные показатели
	_money = 0;
	_reservation_wage = 0;
	_consumption_budget = 0;
	_starve = 0;
	_fed = 0;
}

household::household(double money)
{
	//Реакция внешнего мира
	_salary = 0;
	_employed = false;
	_active = true;
	_employee = 0;
	//Рассчетные показатели
	_money = money;
	_reservation_wage = 1;
	_consumption_budget = 0;
	_starve = 0;
	_fed = 0;
}

//Представленный алгоритм поиска работы пока не учитывает необходимость уволиться с фирмы при устройстве на другую работу.
vector<int> household::searchwork(map<int, double> labordemand)
{
/*    if (_employed && (_salary  < _reservation_wage))
    {
        _employed = false;
		_employee = 0;
    }//*/
	vector<int> possibleemployee; 
	if (_active)
	{
		for(map<int,double>::iterator i = labordemand.begin(); i != labordemand.end(); ++i)
		{
			if ((!_employed) || (_employed && (i->second > _salary)))
				{
					possibleemployee.push_back(i->first);
				}
		}  
	}
	return possibleemployee;
}

int household::chooseemployee(vector<int> proposals, map<int,double> labordemand)
{ 
    if (proposals.size() == 0)
       return _employee;
    double max = labordemand[proposals[0]];
    int maxid = proposals[0];
    for(int i = 1; i < proposals.size(); i++)
    {
       if (labordemand[proposals[i]] > max)
       {
           max = labordemand[proposals[i]];
           maxid = proposals[i];
       }
    }
    _employed = true;
    _salary = max;
	_employee = maxid;
	_active = false;
	return maxid;    
}

void household::work()
{
	_money += _salary;
	_reservation_wage = _salary * 0.8;
	_active = true;
}

void household::quit()
{
	_employed = false;
	_employee = 0;
}

void household::gethelp()
{
	_money += _reservation_wage;
//	_reservation_wage *= 0.8;	
	_active = true;
}

void household::buy_goods(map<int, offer> &demand)
{
    _consumption_budget = consumptionbudget();
	double available = _consumption_budget, spent = 0;
	while ((spent < _consumption_budget) && (demand.size() > 0) && (can_buy(available, demand)))
    {
        map<int,offer>::iterator j = demand.begin();
		int rand = get_random(demand);
		for (int i = 0; i < rand; i++)
		{
			j++;
		}
        buy(j->second, available, spent);
		if ((j->second).get_count() == 0)
		{
			demand.erase(j);
		}//*/

    }
	if (spent > 0)
	{
		_fed++;
		_starve = 0;
	}
	else
	{
		_fed = 0;
		_starve++;
	}
	_money -= spent; 
}

bool household::is_employed()
{
	return _employed;
}

int household::get_employee()
{
	return _employee;
}

double household::getsalary()
{
	return _salary;
}

double household::getmoney()
{
	return _money;
}
double household::getreservation()
{
	return _reservation_wage;
}
double household::getconsumption()
{
	return _consumption_budget;
}

int household::get_starve()
{
	return _starve;
}

int household::get_fed()
{
	return _fed;
}

void household::set_fed(int fed)
{
	_fed = fed;
}

void household::set_salary(double salary)
{
	_salary = salary;
}

double household::consumptionbudget()
{
    if (_money > 0.6 * _salary)
       return (_money - 0.8 * (_money - 0.6 * _salary));
    else
       return (_money);
}

//Покупка товаров, если товар считается бесконечно делимым. В дальнейшем эту процедуру следует переписать так, чтобы товар имел пределы делимости. Например, нельзя купить 0.00000001-ую часть айфона.
void household::buy(offer& good, double& available, double& spent)
{
	if (good.get_count() * good.get_price() >= available)
	{
		spent += available/good.get_price() * available;
		good.set_count(good.get_count() - available/good.get_price());//*/
	/*	spent += floor(available/good.get_price()) * available;
		good.set_count(good.get_count() - floor(available/good.get_price()));	//*/	
	}
	else
	{
		spent += good.get_count() * good.get_price();
		available -= good.get_count() * good.get_price();
		good.set_count(0);
	}
}

void household::printinfo()
{
	cout<<"Salary: "<<_salary<<endl;
	cout<<"Employed: "<<_employed<<endl;
	cout<<"Employee: "<<_employee<<endl;
	cout<<"Money: "<<_money<<endl;
	cout<<"Reservation wage: "<<_reservation_wage<<endl;
	cout<<"Consumption budget :"<<_consumption_budget<<endl;
}

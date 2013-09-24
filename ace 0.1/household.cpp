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
}

//Представленный алгоритм поиска работы пока не учитывает необходимость уволиться с фирмы при устройстве на другую работу.
vector<int> household::searchwork(map<int, double> labordemand)
{
    if (_employed && (_salary  < _reservation_wage))
    {
        _employed = false;
		_employee = 0;
    }
	vector<int> possibleemployee; 
	if (_active)
	{
		for(map<int,double>::iterator i = labordemand.begin(); i != labordemand.end(); i++)
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

void household::gethelp()
{
	_money += _reservation_wage;
	_reservation_wage *= 0.8;	
	_active = true;
}

void household::buygoods(vector<offer> &supply)
{
    _consumption_budget = consumptionbudget();
	double available = _consumption_budget, spent = 0;
	while ((spent < _consumption_budget) && (supply.size() > 0) && (can_buy(available, supply)))
    {
        int j = getrandom(supply);
        buy(supply[j], available, spent);
		if (supply[j].getcount() == 0)
		{
			supply.erase(supply.begin() + j);
		}

    }
	_money -= spent; 
}

bool household::isemployed()
{
	return _employed;
}

int household::getemployee()
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
	if (good.getcount() * good.getprice() >= available)
	{
		spent += floor(available/good.getprice()) * available;
		good.setcount(good.getcount() - floor(available/good.getprice()));		
	}
	else
	{
		spent += good.getcount() * good.getprice();
		available -= good.getcount() * good.getprice();
		good.setcount(0);
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

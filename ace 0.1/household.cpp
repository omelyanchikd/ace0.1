#include "household.h"


household::household(void)
{
	//Идентификатор агента
	_id = 0;
	//Реакция внешнего мира
	_salary = 0;
	_employed = false;
	_employee = 0;
	//Рассчетные показатели
	_money = 0;
	_reservation_wage = 0;
	_consumption_budget = 0;
}

household::household(int id, double money)
{
	//Идентификатор агента
	_id = id;
	//Реакция внешнего мира
	_salary = 0;
	_employed = false;
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
//      L.quit(HouseholdId);
    }
	vector<int> possibleemployee; 
	for(map<int,double>::iterator i = labordemand.begin(); i != labordemand.end(); i++)
    {
       if ((!_employed) || (_employed && (labordemand[i] > _salary)))
       {
		   possibleemployee.push_back(i);
       }
    }  
	return possibleemployee;
}

int household::chooseemployee(vector<vacancy> proposals)
{ 
    if (proposals.size() == 0)
       return 0;
    if (_employed)
    {
       _employed = false;
//     L.quit(HouseholdId);
    }  
    double max = proposals[0].getsalary();
    int maxid = proposals[0].getid();
    for(int i = 1; i < proposals.size(); i++)
    {
       if (proposals[i].getsalary() > max)
       {
           max = proposals[i].getsalary();
           maxid = proposals[i].getid();
       }
    }
    _employed = true;
    _salary = max;
	_employee = maxid;
	return maxid;    
}

void household::work()
{
	_money += _salary;
	_reservation_wage = _salary * 0.8;
}

void household::gethelp()
{
	_money += _reservation_wage;
	_reservation_wage *= 0.8;
}

void household::buygoods(vector<offer> goodsupply)
{
    _consumption_budget = consumptionbudget();
	double available = _consumption_budget, spent = 0;
	while ((spent < _consumption_budget) && (goodsupply.size() > 0))
    {
        int j = getrandom(rand()/(double)RAND_MAX, goodsupply);
        buy(goodsupply[j], available, spent);
		if (goodsupply[j].getcount() == 0)
		{
			goodsupply.erase(goodsupply.begin() + j, goodsupply.begin() + j + 1);
		}

    }
	_money -= spent; 


}

bool household::isemployed()
{
	return _employed;
}

double household::consumptionbudget()
{
    if (_money > 0.6 * _salary)
       return (_money - 0.8 * (_money - 0.6 * _salary));
    else
       return (_money);
}

//Покупка товаров, если товар считается бесконечно делимым. В дальнейшем эту процедуру следует переписать так, чтобы товар имел пределы делимости. Например, нельзя купить 0.00000001-ую часть айфона.
void household::buy(offer good, double& available, double& spent)
{
	if (good.getcount() * good.getprice() >= available)
	{
		spent += available;
		good.setcount(good.getcount() - available/good.getprice());		
	}
	else
	{
		spent += good.getcount() * good.getprice();
		available -= good.getcount() * good.getprice();
		good.setcount(0);
	}
}

int household::getid()
{
	return _id;
}
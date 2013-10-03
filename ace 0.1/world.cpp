#include "world.h"


world::world(void)
{
}

world::world(int firmnumber, int householdnumber, double firmmoney, double householdmoney)
{
	firms.clear();
	households.clear();
	for (int i = 1; i <= firmnumber; i++)
	{
		firms[i] = firm(firmmoney);
	}
	for (int i = 1; i <= householdnumber; i++)
	{
		households[i] = household(householdmoney);
	}
	_goodmarket.clear();
	_labormarket.clear();
}

void world::step()
{
	set_vacancies();
	check_laborinfo();
	for (int iter = 0; iter < 2; iter++)
	{
		set_vacancies();
		set_resumes();
		set_invites();
		choose_employer();
		_labormarket.clear();
	}
	produce();
	get_income();
	set_supply();
	buy();
	get_sales();
	get_statistics();
	write_log();
	firm_learning();
	_goodmarket.clear();
	_labormarket.full_clear();
}

void world::printinfo()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		cout<<"Firm "<<i->first<<": "<<endl;
		(i->second).printinfo();
	}
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		cout<<"Household "<<i->first<<": "<<endl;
		(i->second).printinfo();
	}
}

// ‘ирмы открывают вакансии на рынке труда.
void world::set_vacancies()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		if ((i->second).getworkers() > (i->second).getdesired())
		{
			vector<int> fired;
			fired = (i->second).fire();
			for (int j = 0; j < fired.size(); j++)
			{
				households[j].quit();
			}
		}
		else
		{
			_labormarket.setvacancies(i->first, (i->second).getsalary());	
		}
	}
}


// ѕроверка информации об изменении зарплаты и зан€тости.
void world::check_laborinfo()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		for (int j = 0; j < (i->second).getworkerids().size(); j++)
		{
			households[((i->second).getworkerids())[j]] = (i->second).getsalary();
		}
	}	
}


// ƒомохоз€йства просматривают вакансии этого периода и выбирают, куда устроитьс€.
void world::set_resumes()
{
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		_labormarket.setresumes((i->second).searchwork(_labormarket.getvacancies()), i->first);
	}
}

// ‘ирмы рассматривают списки кандидатов и приглашают на работу потенциальных сотрудников.
void world::set_invites()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_labormarket.setinvites((i->second).checkresumes(_labormarket.getresumes(i->first)), i->first);
	}
}

// ƒомохоз€йства получают предложени€ работы и выбирают работодател€, а фирмы нанимают на работу домохоз€йства, прин€вшие их предложение.
void world::choose_employer()
{
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
//		int currentemployee = (i->second).getemployee();
		int employee = (i->second).chooseemployee(_labormarket.getinvites((i->first)), _labormarket.getvacancies());
		if ((employee != 0)) //&& (employee != currentemployee))
		{
			firms[employee].hire(i->first);
		}
	}
}

//‘ирмы производ€т продукцию
void world::produce()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).produce();
	}
}

//ƒомохоз€йства получают зарплату или пособие по безработице
void world::get_income()
{
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		if ((i->second).isemployed())
			(i->second).work();
/*		else
			(i->second).gethelp();//*/
	}
}

//‘ирмы поставл€ют на рынок товаров продукцию дл€ продажи
void world::set_supply()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_goodmarket.setsupply((i->second).getprice(), (i->second).getstock(), i->first);
	}
}

//ƒомохоз€йства выбирают товары из предложенных
void world::buy()
{
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		(i->second).buygoods(_goodmarket._demand);
	}
}

//‘ирмы забирают полученную выручку
void world::get_sales()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).getsales(_goodmarket.getsales(i->first));
	}
}

void world::firm_learning()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).update();
	}
}

void world::write_log()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_log.setfirmsalary(i->first, (i->second).getsalary());
		_log.setfirmprice(i->first, (i->second).getprice());
		_log.setfirmsold(i->first, (i->second).getsold());
		_log.setfirmworkers(i->first, (i->second).getworkers());
		_log.setfirmmoney(i->first, (i->second).getmoney());
		_log.setfirmprofit(i->first, (i->second).getprofit());
		_log.setfirmdesired(i->first, (i->second).getdesired());
		_log.setfirmstock(i->first, (i->second).getstock());	
	}	
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		_log. sethouseholdsalary(i->first, (i->second).getsalary());
		_log. sethouseholdemployed(i->first, (i->second).isemployed());
		_log. sethouseholdemployee(i->first, (i->second).getemployee());
		_log. sethouseholdmoney(i->first, (i->second).getmoney());
		_log. sethouseholdreservation(i->first, (i->second).getreservation());
		_log. sethouseholdconsumption(i->first, (i->second).getconsumption());
	}
}

double world::unemployment()
{
	int unemployed = 0;
	int household_number = 0;
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		if (!(i->second).isemployed())
		{
			unemployed++;
		}
		household_number++;
	}
	return (double)unemployed/household_number;
}

double world::production()
{
	double sum = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getstock(); // * (i->second).getprice();
	}
	return sum;
}

double world::consumption()
{
	double sum = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice() * (i->second).getsold();
	}
	return sum;
}

double world::average_price()
{
	double sum = 0;
	int firm_number = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice();
		firm_number++;
	}
	return sum/firm_number;
}

double world::average_salary()
{
	double sum = 0;
	int workers = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getsalary() * (i->second).getworkers();
		workers += (i->second).getworkers();
	}
	return sum/workers;
}

double world::inflation()
{
	double sum = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice() * (i->second).getstock();
	}
	return sum/_statistics.inflation();
}

double world::gdp()
{
	double sum = 0;
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		sum += (i->second).getprice() * (i->second).getstock();
	}
	return sum;
}

void world::get_statistics()
{
	_statistics.set_unemployment(unemployment());		// ”ровень безработицы.
	_statistics.set_production(production());			// ќбъем производства.
	_statistics.set_consumption(consumption());			// ќбъем потреблени€.
	_statistics.set_average_price(average_price());		// —редн€€ цена.
	_statistics.set_average_salary(average_salary());	// —редн€€ заработна€ плата.
	_statistics.set_inflation(inflation());				// »нфл€ци€.
	_statistics.set_gdp(gdp());							// ¬аловый внутренний продукт.
}
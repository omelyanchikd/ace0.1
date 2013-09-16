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
	for (int iter = 0; iter < 2; iter++)
	{
		//‘ирмы открывают вакансии на рынке труда
		for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
		{
			_labormarket.setvacancies(i->first, (i->second).postvacancy());	
		}
		//ƒомохоз€йства просматривают вакансии этого периода и выбирают, куда устроитьс€
		for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
		{
			_labormarket.setresumes((i->second).searchwork(_labormarket.getvacancies()), i->first);
		}
		//‘ирмы рассматривают списки кандидатов и приглашают на работу потенциальных сотрудников
		for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
		{
			_labormarket.setinvites((i->second).checkresumes(_labormarket.getresumes(i->first)), i->first);
		}
		//ƒомохоз€йства получают предложени€ работы и выбирают работодател€, а фирмы нанимают на работу домохоз€йства, прин€вшие их предложение
		for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
		{
			firms[(i->second).chooseemployee(_labormarket.getresumes((i->first)), _labormarket.getvacancies())].hire(i->first);
		}
		_labormarket.clear();
	}
	//‘ирмы производ€т продукцию
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).produce();
	}
	//ƒомохоз€йства получают зарплату или пособие по безработице
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		if ((i->second).isemployed())
			(i->second).work();
		else
			(i->second).gethelp();
	}
	//‘ирмы поставл€ют на рынок товаров продукцию дл€ продажи
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_goodmarket.setsupply((i->second).getprice(), (i->second).getstock(), i->first);
	}
	//ƒомохоз€йства выбирают товары из предложенных
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		(i->second).buygoods(_goodmarket.getdemand());
	}
	//‘ирмы забирают полученную выручку
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).getsales(_goodmarket.getsales(i->first));
	}
	_goodmarket.clear();
}

void world::printinfo()
{
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		cout<<"Firm "<<i->first<<": ";
		(i->second).printinfo();
	}
	for (map<int, household>::iterator i = households.begin(); i != households.end(); i++)
	{
		cout<<"Household "<<i->first<<": ";
		(i->second).printinfo();
	}
}




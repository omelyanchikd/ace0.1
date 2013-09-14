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
		//firms[i] = firm firmmoney));
	}
	for (int i = 0; i < householdnumber; i++)
	{
		households.push_back(household(i+1, householdmoney));
	}
	goodsupply.clear();
	gooddemand.clear();
	goodsupplyinfo.clear();
	_labormarket.clear();
}

void world::step()
{
	goodsupply.clear();
	gooddemand.clear();
	goodsupplyinfo.clear();
	for (int iter = 0; iter < 2; iter++)
	{
		//‘ирмы открывают вакансии на рынке труда
		for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
		{
			_labormarket.setvacancies(i->first, (i->second).postvacancy());	
		}
		//ƒомохоз€йства просматривают вакансии этого периода и выбирают, куда устроитьс€
		for (int i = 0; i < households.size(); i++)
		{
			_labormarket.setresumes(households[i].searchwork(_labormarket.getvacancies()), households[i].getid());
		}
		//‘ирмы рассматривают списки кандидатов и приглашают на работу потенциальных сотрудников
		for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
		{
			_labormarket.setinvites((i->second).checkresumes(_labormarket.getresumes(i->first)), i->first);
		}
		//ƒомохоз€йства получают предложени€ работы и выбирают работодател€, а фирмы нанимают на работу домохоз€йства, прин€вшие их предложение
		for (int i = 0; i < households.size(); i++)
		{
			firms[households[i].chooseemployee(_labormarket.getresumes(households[i].getid()), _labormarket.getvacancies())].hire(households[i].getid());
		}
		_labormarket.clear();
	}
	//‘ирмы производ€т продукцию
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).produce();
	}
	//ƒомохоз€йства получают зарплату или пособие по безработице
	for (int i = 0; i < households.size(); i++)
	{
		if (households[i].isemployed())
			households[i].work();
		else
			households[i].gethelp();
	}
	//‘ирмы поставл€ют на рынок товаров продукцию дл€ продажи
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		_goodmarket.setsupply((i->second).postoffer());
	}
	goodsupplyinfo = duplicate<offer>(goodsupply);
	//ƒомохоз€йства выбирают товары из предложенных
	for (int i = 0; i < households.size(); i++)
	{
		households[i].buygoods(goodsupply);
	}
	//‘ирмы забирают полученную выручку
	for (map<int, firm>::iterator i = firms.begin(); i != firms.end(); i++)
	{
		(i->second).getsales(sales(i->first));
	}
}




double world::sales(int firmid)
{
//	double stock = getcount(firmid, goodsupplyinfo);
//	double unsold = getcount(firmid, goodsupply);
//	double price = getprice(firmid, goodsupplyinfo);
//	return (stock - unsold);
	return 0;
}


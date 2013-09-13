#include "world.h"


world::world(void)
{
}

world::world(int firmnumber, int householdnumber, double firmmoney, double householdmoney)
{
	firms.clear();
	households.clear();
	for (int i = 0; i < firmnumber; i++)
	{
		firms.push_back(firm(i+1, firmmoney));
	}
	for (int i = 0; i < householdnumber; i++)
	{
		households.push_back(household(i+1, householdmoney));
	}
	goodsupply.clear();
	gooddemand.clear();
	goodsupplyinfo.clear();

	_labordemand.clear();
	_laborsupply.clear();
	_invitations.clear();
}

void world::step()
{
	goodsupply.clear();
	gooddemand.clear();
	goodsupplyinfo.clear();
	for (int iter = 0; iter < 2; iter++)
	{
		_labordemand.clear();
		_laborsupply.clear();
		_invitations.clear();
		//‘ирмы открывают вакансии на рынке труда
		for (int i = 0; i < firms.size(); i++)
		{
			_labormarket.setvacancies(firms[i].postvacancy());	
		}
		_laborsupply.resize(_labordemand.size());
		_invitations.resize(households.size());
		//ƒомохоз€йства просматривают вакансии этого периода и выбирают, куда устроитьс€
		for (int i = 0; i < households.size(); i++)
		{
			_labormarket.setresumes(households[i].searchwork(_labormarket.getvacancies()), households[i].getid());
		}
		//‘ирмы рассматривают списки кандидатов и приглашают на работу потенциальных сотрудников
		for (int i = 0; i < firms.size(); i++)
		{
			_labormarket.setinvites(firms[i].checkresumes(_labormarket.getresumes(firms[i].getid())), firms[i].getid());
		}
		//ƒомохоз€йства получают предложени€ работы и выбирают работодател€, а фирмы нанимают на работу домохоз€йства, прин€вшие их предложение
		for (int i = 0; i < households.size(); i++)
		{
			firms[households[i].chooseemployee(_invitations[i])].hire(households[i].getid());
		}
	}
	//‘ирмы производ€т продукцию
	for (int i = 0; i < firms.size(); i++)
	{
		firms[i].produce();
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
	for (int i = 0; i < firms.size(); i++)
	{
		goodsupply.push_back(firms[i].postoffer());
	}
	goodsupplyinfo = duplicate<offer>(goodsupply);
	//ƒомохоз€йства выбирают товары из предложенных
	for (int i = 0; i < households.size(); i++)
	{
		households[i].buygoods(goodsupply);
	}
	//‘ирмы забирают полученную выручку
	for (int i = 0; i < firms.size(); i++)
	{
		firms[i].getsales(sales(firms[i].getid()));
	}
}




double world::sales(int firmid)
{
	double stock = getcount(firmid, goodsupplyinfo);
	double unsold = getcount(firmid, goodsupply);
//	double price = getprice(firmid, goodsupplyinfo);
	return (stock - unsold);
}


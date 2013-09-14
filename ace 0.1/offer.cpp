#include "offer.h"


offer::offer(void)
{
	_count = 0;
	_price = 0;
	_firmid = 0;
}

double offer::getprice()
{
	return _price;
}

double offer::getcount()
{
	return _count;
}

int offer::getid()
{
	return _firmid;
}

void offer::setcount(double value)
{
	_count = value;
}

int getrandom(double value, vector<offer> goodsupply)
{
    vector<double> distribution;
    distribution.push_back(0);
    for (int i = 0; i < goodsupply.size(); i++)
    {
       distribution.push_back(goodsupply[i].getprice() + distribution[i]);
    }
    for (int i = 0; i < goodsupply.size(); i++)
    {
        if ((distribution[i] <= value) && (value <= distribution[i+1]))
           return (i+1);
    }
    return goodsupply.size();
}

double getprice(int firmid, vector<offer> goodsupply)
{
	for (int i = 0; i < goodsupply.size(); i++)
	{
		if (goodsupply[i].getid() == firmid)
			return goodsupply[i].getprice();
	}
	return 0;
}

double getcount(int firmid, vector<offer> goodsupply)
{
	for (int i = 0; i < goodsupply.size(); i++)
	{
		if (goodsupply[i].getid() == firmid)
			return goodsupply[i].getcount();
	}
	return 0;
}

bool isin(int firmid, vector<offer> goodsupply)
{
	for (int i = 0; i < goodsupply.size(); i++)
	{
		if (goodsupply[i].getid() == firmid)
			return true;
	}
	return false;
}





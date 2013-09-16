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

void offer::setcount(double value)
{
	_count = value;
}

int offer::getid()
{
	return _firmid;
}

int getrandom(double value, vector<offer> gooddemand)
{
    vector<double> probabilities;
	vector<double> distribution;
	distribution.clear();
	probabilities.clear();
	for(int i = 0; i <gooddemand.size(); i++)
	{
		probabilities.push_back(1/gooddemand[i].getprice());
		distribution.push_back(0);

	}
    distribution.push_back(0);
    for (int i = 1; i < probabilities.size(); i++)
    {
       distribution[i]=probabilities[i] + distribution[i-1];  
    }
	for (int i = 0; i < probabilities.size(); i++)
    {
        if ((distribution[i] <= value) && (value <= distribution[i+1]))
           return (gooddemand[i].getid());
    }
    return 0;
}

double getcount(int firmid, vector<offer> good)
{
	for (int i = 0; i < good.size(); i++)
	{
		if (i == firmid)
			return good[i].getcount();
	}
	return 0;
}




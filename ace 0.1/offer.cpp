#include "offer.h"


offer::offer(void)
{
	_count = 0;
	_price = 0;
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

int getrandom(double value, map<int,offer> supply)
{
    vector<double> probabilities;
	probabilities.clear();
	for(map<int, offer>::iterator i = supply.begin(); i != supply.end(); i++)
	{
		probabilities[i].push_back(1/(i->second).getprice());
	}
	vector<double> distribution;
	distribution.clear();
    distribution.push_back(0);
    for (int i = 1; i < probabilities.size(); i++)
    {
       distribution[i]=probabilities[i] + distribution[i-1];  
    }
	for (int i = 0; i < probabilities.size(); i++)
    {
        if (distribution[i] <= value) && (value <= distribution[i])
           return ((supply.begin()+i)->first);
    }
    return 0;
}






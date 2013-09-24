#include "offer.h"

boost::mt19937 random_generator(1000);

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

double getcount(int firmid, vector<offer> good)
{
	for (int i = 0; i < good.size(); i++)
	{
		if (i+1 == firmid)
			return good[i].getcount();
	}
	return 0;
}

// Разобраться с генератором псевдослучайных чисел.
int getrandom(vector<offer> gooddemand)
{
	vector<double> probabilities;
	for(int i = 0; i < gooddemand.size(); i++)
	{
		probabilities.push_back(1/gooddemand[i].getprice());

	}
	boost::random::discrete_distribution<> get_rand(probabilities.begin(), probabilities.end());
	return get_rand(random_generator);
}

bool can_buy(double money, vector<offer> good)
{
	for (int i = 0; i < good.size(); i++)
	{
		if (money >= good[i].getprice())
			return true;
	}
	return false;
}

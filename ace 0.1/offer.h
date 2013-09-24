#pragma once

#include <vector>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/discrete_distribution.hpp>

using namespace std;

class offer
{
public:
	offer(void);
	offer(double price, double count, int firmid): _price(price), _count(count), _firmid(firmid)
	{
	}
	double getprice();
	double getcount();
	
	void setcount(double value);
	int getid();

private:
	double _count;
	double _price;
	int _firmid;
};

int getrandom(vector<offer> gooddemand);

double getcount(int firmid, vector<offer> good);

bool can_buy(double money, vector<offer> good);


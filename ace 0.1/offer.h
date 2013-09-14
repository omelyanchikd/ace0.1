#pragma once

#include <map>

using namespace std;

class offer
{
public:
	offer(void);
	offer(double count, double price): _count(count), _price(price)
	{
	}
	double getprice();
	double getcount();
	
	void setcount(double value);

private:
	double _count;
	double _price;
};

int getrandom(double value, map<int, offer> supply);


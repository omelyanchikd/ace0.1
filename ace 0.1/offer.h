#pragma once

#include <vector>

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

int getrandom(double value, vector<offer> gooddemand);

double getcount(int firmid, vector<offer> good);


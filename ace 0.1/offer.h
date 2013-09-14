#pragma once

#include <vector>

using namespace std;

class offer
{
public:
	offer(void);
	offer(double count, double price, int firmid): _count(count), _price(price), _firmid(firmid)
	{
	}
	double getprice();
	double getcount();
	int getid();
	
	void setcount(double value);

private:
	double _count;
	double _price;
	int _firmid;
};

int getrandom(double value, vector<offer> goodsupply);

double getprice(int firmid, vector<offer> goodsupply);

double getcount(int firmid, vector<offer> goodsupply);

bool isin(int firmid, vector<offer> goodsupply);
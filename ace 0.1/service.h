#pragma once

#include <vector>

using namespace std;

template <class T> bool isin(vector<T> v, T el)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (el == v[i])
			return true;
	}
	return false;
}

template <class T> vector<T> duplicate(vector<T> v)
{
	vector<T> c;
	c.clear();
	for (int i = 0; i < v.size(); i++)
	{
		c.push_back(v[i]);
	}
	return c;
}





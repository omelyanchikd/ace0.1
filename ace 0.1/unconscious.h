#pragma once

#include <vector>

using namespace std;

class unconscious
{
public:
	unconscious(int n);
	void update(double reward);
	int get_action();
private:
	vector<double> _probabilities;
	int _action;
};


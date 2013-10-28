#pragma once

#include <vector>

using namespace std;

class qlearning
{
public:
	
	qlearning(void);
	void init(int state, int action, double value);
	void update(int state, double reward);
	int get_action();

private:
	
	double max(int state);
	int argmax();

	int _state;
	int _action;
	vector<double> q;
	double learning_factor;
	double discount_factor;
	int s_n;
	int a_n;
};


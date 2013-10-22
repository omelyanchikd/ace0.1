#include "qlearning.h"


qlearning::qlearning(void)
{
}

void qlearning::init(int state, int action)
{
	for (int i = 0; i < state * action; i++)
	{
		q.push_back(1.0 / (state * action));
	}
}

void qlearning::update(int state, double reward)
{
	q[s_n * _action + _state] += learning_factor * (reward + discount_factor * max(state) - q[s_n * _action + _state] );   
	_state = state;
	double eps = rand() / (double)RAND_MAX;
	if (eps >= 0.4)
	{
		_action = argmax();
	}
	else
	{
		_action = rand() % a_n;
	}
}

int qlearning::get_action()
{
	return _action;
}

double qlearning::max(int state)
{
	double max = q[s_n * state];
	for (int i = s_n * state + 1; i < s_n * state + a_n; i++)
	{
		if (q[i] > max)
			max = q[i];
	}
	return max;
}

int qlearning::argmax()
{
	int maxid = 0;
	for (int i = s_n * _state + 1; i < s_n * _state + a_n; i++)
	{
		if (q[i] > q[maxid])
			maxid = i;
	}
	return (maxid - s_n * _state);

}
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
	q[s_n * _action + _state] =  
}

#include "unconscious.h"

boost::mt19937 r_gen(1000);

unconscious::unconscious()
{
	_action = 0;
}

void unconscious::init(int n)
{
	for (int i = 0; i < n; i++)
	{
		_probabilities.push_back(1.0/n);
	}
	_action = 0;
}

void unconscious::update(double reward)
{	
	double old_probability = _probabilities[_action];
	for (int i = 0; i < _probabilities.size(); i++)
	{
		if (reward > 0)
		{
			if (i == _action)
			{
				_probabilities[i] += transform(reward) * (1 - _probabilities[i]); 
			}
			else
			{
				_probabilities[i] += -transform(reward) * _probabilities[i];
			}
		}
		else
		{
			if (i == _action)
			{
				_probabilities[i] += -transform(-reward) * _probabilities[i]; 
			}
			else
			{
				_probabilities[i] += transform(-reward) * old_probability * _probabilities[i]/(1 - old_probability);
			}
		}
	}
	boost::random::discrete_distribution<> get_rand(_probabilities.begin(), _probabilities.end());
	_action = get_rand(r_gen);
}

int unconscious::get_action()
{
	return _action;
}

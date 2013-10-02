#include "unconscious.h"


unconscious::unconscious(int n)
{
	for (int i = 0; i < n; i++)
	{
		_probabilities.push_back(1.0/n);
	}
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
				_probabilities[i] += reward * (1 - _probabilities[i]); 
			}
			else
			{
				_probabilities[i] += -reward * _probabilities[i];
			}
		}
		else
		{
			if (i == _action)
			{
				_probabilities[i] += - reward * _probabilities[i]; 
			}
			else
			{
				_probabilities[i] += -reward * old_probability * _probabilities[i]/(1 - old_probability);
			}
		}
	}
}


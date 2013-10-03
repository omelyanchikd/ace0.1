#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#define _USE_MATH_DEFINES
#include "math.h"

#include <vector>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/discrete_distribution.hpp>

using namespace std;

class unconscious
{
public:
	unconscious();
	void init(int n);
	void update(double reward);
	int get_action();
private:
	vector<double> _probabilities;
	int _action;
};

//inline double transform(double x) {return (2/(1+exp(-x/10000))-1);};
inline double transform(double x) {return (M_2_PI*atan(x/1000));};
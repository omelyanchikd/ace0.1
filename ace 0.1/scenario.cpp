#include "scenario.h"

scenario::scenario(void)
{
	method = nonconscious;
	way = value;
	parameters = salary_desired;
	criteria = profit;
}

void scenario::init(method_type _method, way_type _way, parameters_type _parameters, criteria_type _criteria)
{
	method = _method;
	way = _way;
	parameters = _parameters;
	criteria = _criteria;
}
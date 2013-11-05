#pragma once

enum method_type {random, rational_quantity, rational_salary, intuitive, oligopoly, recursive_least_squares, rlsf, nonconscious, q_learning, classifiers, neural_network, evolution};
enum way_type {value, change, share};
enum parameters_type{salary_price_desired, salary_desired, salary_price_plan, salary_plan}; // Rewrite later.
enum criteria_type{profit, workers, return_rate, sales_change, forecast};

class scenario
{
public:
	scenario(void);

	scenario(method_type _method, way_type _way, parameters_type _parameters, criteria_type _criteria): method(_method), way(_way), parameters(_parameters), criteria(_criteria)
	{
	}

	void init(method_type _method, way_type _way, parameters_type _parameters, criteria_type _criteria);


	method_type method;
	way_type way;
	parameters_type parameters;
	criteria_type criteria;
	
};


#include "firms.h"


firms::firms(void)
{
}

firms::firms(int n, double money, string model_name)
{
	for (int i = 0; i < n; i++)
	{
		_firms[i+1] = (firm(money));
	}
	vector<double> fi;
	fi.push_back(104);
	fi.push_back(-1.0/3);
	_rls = rls(fi, matrix(2));
	ofstream fout;
	ostringstream fn;
	for (int i = 1; i < n+1; i++)
	{
		fn<<model_name<<"_salary"<<"_firm_"<<i<<".txt";
		fout.open(fn.str());
		fout.clear();
		fout.close();
		fn.str("");
		fn<<model_name<<"_price"<<"_firm_"<<i<<".txt";
		fout.open(fn.str());
		fout.clear();
		fout.close();
		fn.str("");;
		fn<<model_name<<"_sold"<<"_firm_"<<i<<".txt";
		fout.open(fn.str());
		fout.clear();
		fout.close();
		fn.str("");
		fn<<model_name<<"_workers"<<"_firm_"<<i<<".txt";
		fout.open(fn.str());
		fout.clear();
		fout.close();
		fn.str("");
		fn<<model_name<<"_money"<<"_firm_"<<i<<".txt";
		fout.open(fn.str());
		fout.clear();
		fout.close();
		fn.str("");
		fn<<model_name<<"_profit"<<"_firm_"<<i<<".txt";
		fout.open(fn.str());
		fout.clear();
		fout.close();
		fn.str("");
		fn<<model_name<<"_desired"<<"_firm_"<<i<<".txt";
		fout.open(fn.str());
		fout.clear();
		fout.close();
		fn.str("");
		fn<<model_name<<"_stock"<<"_firm_"<<i<<".txt";
		fout.open(fn.str());
		fout.clear();
		fout.close();
		fn.str("");
	}
	fn<<model_name<<"_average_price.txt";
	fout.open(fn.str());
	fout.clear();
	fout.close();
	fn.str("");
	fn<<model_name<<"_average_salary.txt";
	fout.open(fn.str());
	fout.clear();
	fout.close();
	fn.str("");
	fn<<model_name<<"_gdp.txt";
	fout.open(fn.str());
	fout.clear();
	fout.close();
	fn.str("");
	fn<<model_name<<"_consumption.txt";
	fout.open(fn.str());
	fout.clear();
	fout.close();
	fn.str("");
	fn<<model_name<<"_production.txt";
	fout.open(fn.str());
	fout.clear();
	fout.close();
	fn.str("");
	fn<<model_name<<"_firm_number.txt";
	fout.open(fn.str());
	fout.clear();
	fout.close();
	fn.str("");
}

void firms::buy_raw(double price)
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
			(i->second).buy_raw(price);			
	}
}

map<int, double> firms::set_vacancies()
{
	map<int, double> vacancies;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
//		if ((i->second).getworkers() < (i->second).getdesired())
//		{
			vacancies[i->first] = (i->second).getsalary();			
//		}
	}
	return vacancies;
}

vector<int> firms::fire()
{
	vector<int> fired;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		if ((i->second).getworkers() > (i->second).getdesired())
		{
			vector<int> decision = (i->second).fire();
			fired.insert(fired.end(),decision.begin(), decision.end());
			decision.clear();
		}
	}
	return fired;
}

map<int, vector<int>> firms::check_resumes(map<int, vector<int>> resumes)
{
	map<int, vector<int>> invites;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		invites[i->first] = (i->second).checkresumes(resumes[i->first]);
	}
	return invites;
}

void firms::hire(map<int, vector<int>> employers)
{
	for (map<int, vector<int>>::iterator i = employers.begin(); i != employers.end(); ++i)
	{
		_firms[i->first].hire(i->second);
	}
}

void firms::produce()
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		(i->second).produce();
	}
}

map<int, offer> firms::set_supply()
{
	map<int, offer> supply;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		supply[i->first] = offer((i->second).getprice(), (i->second).getstock());
	}
	return supply;
}

void firms::get_sales(map<int, int> sales)
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		(i->second).getsales(sales[i->first]);
	}
}

void firms::learn(vector<vector<double>> rules_price, vector<vector<double>> rules_salary, vector<vector<double>> rules_plan)
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		(i->second).learn(rules_price, rules_salary, rules_plan);
	}
}

void firms::learn(scenario _scenario)
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		(i->second).learn(_scenario);
	}
}

void firms::write_log(data& _log)
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		_log.setfirmsalary(i->first, (i->second).getsalary());
		_log.setfirmprice(i->first, (i->second).getprice());
		_log.setfirmsold(i->first, (i->second).getsold());
		_log.setfirmworkers(i->first, (i->second).getworkers());
		_log.setfirmmoney(i->first, (i->second).getmoney());
		_log.setfirmprofit(i->first, (i->second).getprofit());
		_log.setfirmdesired(i->first, (i->second).getdesired());
		_log.setfirmstock(i->first, (i->second).getstock());	
		_log.setfirmaction(i->first, (i->second).getaction());
	}	
}

void firms::write_log(string model_name)
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		(i->second).write_log(model_name, i->first);
		//_log.setfirmaction(i->first, (i->second).getaction());
	}	
	ofstream fout;
	ostringstream fn;
	fn<<model_name<<"_average_price.txt";
	fout.open(fn.str(), ios_base::app);
	fout<<average_price()<<" ";;
	fout.close();
	fn.str("");
	fn<<model_name<<"_average_salary.txt";
	fout.open(fn.str(), ios_base::app);
	fout<<average_salary()<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_gdp.txt";
	fout.open(fn.str(), ios_base::app);
	fout<<gdp()<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_consumption.txt";
	fout.open(fn.str(), ios_base::app);
	fout<<consumption()<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_production.txt";
	fout.open(fn.str(), ios_base::app);
	fout<<production()<<" ";
	fout.close();
	fn.str("");
	fn<<model_name<<"_firm_number.txt";
	fout.open(fn.str(), ios_base::app);
	fout<<firm_number()<<" ";
	fout.close();
	fn.str("");
}

void firms::clear()
{
	_firms.clear();
}

void firms::print_info()
{
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		cout<<"Firm "<<i->first<<": "<<endl;
		(i->second).printinfo();
	}
}

double firms::production()
{
	double sum = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		sum += (i->second).getstock(); // * (i->second).getprice();
	}
	return sum;
}

double firms::consumption()
{
	double sum = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		sum += (i->second).getsold();
	}
	return sum;
}

double firms::average_price()
{
	double sum = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		sum += (i->second).getprice();
	}
	return sum/firm_number();
}

double firms::average_salary()
{
	double sum = 0;
	int workers = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		sum += (i->second).getsalary() * (i->second).getworkers();
		workers += (i->second).getworkers();
	}
	return sum/workers;
}

double firms::gdp()
{
	double sum = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		sum += (i->second).getprice() * (i->second).getstock();
	}
	return sum;
}

int firms::firm_number()
{
	return _firms.size();
}

double firms::b()
{
	double xy = 0;
	double xx = 0;
	double sum_x = 0;
	double sum_y = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i) 
	{
		xy += (i->second).getsold() * (i->second).getprice();
		xx += (i->second).getsold() * (i->second).getsold();
		sum_x += (i->second).getsold();
		sum_y += (i->second).getprice();
	}
	if (firm_number() * xx - sum_x * sum_x == 0)
		return 0;
	return (firm_number() * xy - sum_x * sum_y) / (firm_number() * xx - sum_x * sum_x);	
}

double firms::a()
{
	double xy = 0;
	double xx = 0;
	double sum_x = 0;
	double sum_y = 0;
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i) 
	{
		xy += (i->second).getsold() * (i->second).getprice();
		xx += (i->second).getsold() * (i->second).getsold();
		sum_x += (i->second).getsold();
		sum_y += (i->second).getprice();
	}
	if (firm_number() * xx - sum_x * sum_x == 0)
		return sum_y/firm_number();
	double b = (firm_number() * xy - sum_x * sum_y) / (firm_number() * xx - sum_x * sum_x);		
	return  (- b * sum_x + sum_y) / firm_number();
}

void firms::set_info()
{	
	vector<double> x;
	x.push_back(1);
	x.push_back(production());
	_rls.update(average_price(), x);
	x.clear();
	x = _rls.get_action();
	int _f = firm_number();
	for (map<int, firm>::iterator i = _firms.begin(); i != _firms.end(); ++i)
	{
		(i->second).set_info(x[0], -x[1], _f);
	}
}
#pragma once

#include <vector>
#include <map>

#include "household.h"

#include "data.h"

using namespace std;

class households
{
public:
	// ������������.
	households(void);
	households(int n, double money);
	// ����� �����.
	map<int, vector<int>> search_work(map<int,double> vacancies);
	map<int, vector<int>> choose_employee(map<int, vector<int>> invites, map<int, double> vacancies);
	void quit(vector<int> fired);
	void update_salary(map<int, double> salaries);
	// ������������.
	void get_income();
	// ����� �������.
	void buy(map<int, offer> &demand);
	// �������� ����������.
	void write_log(data& _log);
	void write_log(char* _log);
	// ����� ����������.
	void print_info();
	// �������.
	void clear();
	// ����������.
	double unemployment();
	int household_number();
private:
	map<int, household> _households;
};


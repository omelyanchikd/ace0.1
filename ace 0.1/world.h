#pragma once

#include "firms.h"
#include "households.h"

#include "labormarket.h"
#include "goodmarket.h"

#include "data.h"
#include "macro.h"

#include "offer.h"



#include <vector>
#include <map>

class world
{
public:
	
	world(void);
	world(int firmnuumber, int householdnumber, double firmmoney, double householdmoney);
	
	void step();

	void printinfo();

	data _log;
	macro _statistics;

private:

	firms _firms;
	households _households;
	
	labormarket _labormarket;
	goodmarket _goodmarket;
	
	void check_laborinfo();		// �������� ���������� �� ��������� �������� � ���������.
	void get_statistics();		// ���������� �������� �������������� �����������.
	void erase_vacancies();		// �������� ����������� ��������.
	void check_workers();		// �������� �����������.
	// ����������.
	double unemployment();		// ������� �����������.
	double production();		// ����� ������������.
	double consumption();		// ����� �����������.
	double average_price();		// ������� ����.
	double average_salary();	// ������� ���������� �����.
	double inflation();			// ��������.
	double gdp();				// ������� ���������� �������.

};


#pragma once

#include "firm.h"
#include "household.h"

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

	map<int, firm> firms;
	map<int, household> households;
	
	labormarket _labormarket;
	goodmarket _goodmarket;
	
	void set_vacancies();  		// ����� ��������� ������� �� �������� �������� �� ����� ����� ��� ���������� �����������.
	void set_resumes();	    	// ������������� ������������� �������� ����� ������� � ��������, ���� ����������.
	void set_invites();	    	// ����� ������������� ������ ���������� � ���������� �� ������ ������������� �����������.
	void choose_employer();     // ������������� �������� ����������� ������ � �������� ������������, � ����� �������� �� ������ �������������, ��������� �� �����������.
	void produce();         	// ����� ���������� ���������.
	void get_income();	        // ������������� �������� �������� ��� ������� �� �����������.
	void set_supply();			// ����� ���������� �� ����� ������� ��������� ��� �������.
	void buy();					// ������������� �������� ������ �� ������������.
	void get_sales();			// ����� �������� ���������� �������.
	void firm_learning();		// ����� ��������� ���� ��������� �� ����������� ��������.
	void write_log();           // ��������� ���� ���� ����������� ������ ����������.
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


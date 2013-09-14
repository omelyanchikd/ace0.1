#pragma once

#include "vacancy.h"

#include <map>
#include <vector>

using namespace std;

class labormarket
{
public:
	labormarket(void);

	void setvacancies(vacancy _vacancy);
	map<int,double> getvacancies();

	void setresumes(vector<int> resumes, int householdid);
	vector<int> getresumes(int firmid);

	void setinvites(vector<int> invites, int firmid);

private:
	map<int,double> _vacancies;
	map<int, vector<int>> _resumes;	

};


#pragma once

#include <map>
#include <vector>

using namespace std;

class labormarket
{
public:
	labormarket(void);

	void setvacancies(int firmid, double salary);
	map<int,double> getvacancies();

	void setresumes(vector<int> resumes, int householdid);
	vector<int> getresumes(int firmid);

	void setinvites(vector<int> invites, int firmid);
	vector<int> getinvites(int firmid);

	void clear();
	void full_clear();

	void erase_vacancy(int i);
	
private:
	map<int,double> _vacancies;
	map<int, vector<int>> _resumes;	
	map<int, vector<int>> _invites;

};


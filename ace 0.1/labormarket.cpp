#include "labormarket.h"


labormarket::labormarket(void)
{

}

void labormarket::setvacancies(int firmid, double salary)
{
	_vacancies[firmid] = salary;
}

map<int, double> labormarket::getvacancies()
{
	return _vacancies;
}

void labormarket::setresumes(vector<int> resumes, int householdid)
{
	for (int i = 0; i < resumes.size(); i++)
	{
		_resumes[resumes[i]].push_back(householdid);
	}
}

vector<int> labormarket::getresumes(int firmid)
{
	return _resumes[firmid];
}

void labormarket::setinvites(vector<int> invites, int firmid)
{
	_resumes.clear();
	for (int i = 0; i < invites.size(); i++)
	{
		_resumes[invites[i]].push_back(firmid);
	}
}

void labormarket::clear()
{
	_vacancies.clear();
	_resumes.clear();
}
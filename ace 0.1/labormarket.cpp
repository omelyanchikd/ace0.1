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
	for (int i = 0; i < invites.size(); i++)
	{
		_invites[invites[i]].push_back(firmid);
	}
}

vector<int> labormarket::getinvites(int firmid)
{
	return _invites[firmid];
}


void labormarket::full_clear()
{
	_vacancies.clear();
	_resumes.clear();
	_invites.clear();
}

void labormarket::clear()
{
	_resumes.clear();
	_invites.clear();
}

void labormarket::erase_vacancy(int i)
{
	_vacancies.erase(i);
}
#include "labormarket.h"


labormarket::labormarket(void)
{

}

void labormarket::set_vacancies(map<int, double> vacancies)
{
	_vacancies = vacancies;
}

map<int, double> labormarket::get_vacancies()
{
	return _vacancies;
}

void labormarket::set_resumes(map<int, vector<int>> resumes)
{
	for (map<int,vector<int>>::iterator i = resumes.begin(); i != resumes.end(); i++)
	{
		for (int j = 0; j < (i->second).size(); j++)
		{
			_resumes[j].push_back(i->first);
		}
	}
}

map<int, vector<int>> labormarket::get_resumes()
{
	return _resumes;
}

void labormarket::set_invites(map<int, vector<int>> invites)
{
	for (map<int,vector<int>>::iterator i = invites.begin(); i != invites.end(); i++)
	{
		for (int j = 0; j < (i->second).size(); j++)
		{
			_invites[j].push_back(i->first);
		}
	}
}

map<int, vector<int>> labormarket::get_invites()
{
	return _invites;
}

void labormarket::set_employer()
{
}

map<int, int> labormarket::get_employer()
{

}

void labormarket::full_clear()
{
	_vacancies.clear();
	_resumes.clear();
	_invites.clear();
	_employer.clear();
}

void labormarket::clear()
{
	_vacancies.clear();
	_resumes.clear();
	_invites.clear();
	_employer.clear();
}

void labormarket::erase_vacancy(int i)
{
	_vacancies.erase(i);
}
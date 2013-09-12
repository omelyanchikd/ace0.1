#include "labormarket.h"


labormarket::labormarket(void)
{

}

void labormarket::setvacancies(vacancy _vacancy)
{
	_vacancies[_vacancy.getid()] = _vacancy.getsalary();
}

map<int, double> labormarket::getvacancies()
{
	return _vacancies;
}

void labormarket::setresumes(vector<int> resumes, int householdid)
{
	_resumes[householdid] = resumes;
}
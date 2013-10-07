#pragma once

#include <map>
#include <vector>

using namespace std;

class labormarket
{
public:
	labormarket(void);

	void set_vacancies(map<int, double> vacancies);
	map<int,double> get_vacancies();

	void set_resumes(map<int, vector<int>> resumes);
	map<int, vector<int>> get_resumes();

	void set_invites(map<int, vector<int>> invites);
	map<int, vector<int>> get_invites();

	void set_employer(map<int, int> employer);
	map<int, int> get_employer();

	void clear();
	void full_clear();

	void erase_vacancy(int i);
	
private:
	map<int, double> _vacancies;
	map<int, vector<int>> _resumes;	
	map<int, vector<int>> _invites;
	map<int, int> _employer;

};


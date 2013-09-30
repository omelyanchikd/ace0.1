// ace 0.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "world.h"


int _tmain(int argc, _TCHAR* argv[])
{
	srand(1);
	int n = 3, m = 15, i = 4;
/*	cout<<"Input initial number of firms: "<<endl;
	cin>>n;
	cout<<"Input initial number of households: "<<endl;
	cin>>m;
	cout<<"Input initial number of iterations: "<<endl;
	cin>>i;//*/
	world earth(n,m,100,10);
	for (int iteration = 0; iteration < i; iteration++)
	{
		earth.step();
		cout<<"Iteration "<<iteration<<endl;
		//earth.printinfo();
	}
	earth._log.printinfo();
	cin>>n;
	return 0;
}


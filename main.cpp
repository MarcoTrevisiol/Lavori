#include <cstdlib>
#include <iostream>
#include "griglia.h"
#include "motore.h"
#include <ctime>

using namespace std;

int main()
{
	srand(time(0));
	Motore m;
	
	m.stampa();
	cout<<"\n";
	
	int c;
	cin>>c;
	while (c!=0)
	{
		switch(c)
		{
			case 2:m.muovi(su);
				break;
			case 3:m.muovi(giu);
				break;
			case 1:m.muovi(sx);
				break;
			case 4:m.muovi(dx);
				break;
		}
		m.stampa();
		cout<<'\n';
		cin>>c;
		cout<<'\n';
	}
	
	
	return 0;
}

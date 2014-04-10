#ifndef _MOTORE_
#define _MOTORE_

#include "griglia.h"
#include <cstdlib>

using namespace std;

class Motore
{
	private:
		Griglia * g;
		cas a;
		void settile();
	public:
		Motore(Griglia * gr = 0);
		void muovi(mossa m);
		void stampa();
};

#endif

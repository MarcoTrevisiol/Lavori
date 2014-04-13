#ifndef _MOTORE_
#define _MOTORE_

#include "griglia.h"
#include <cstdlib>
#include "ia.h"

using namespace std;

#define prob1r2	4

class Motore
{
	private:
		Griglia * g;
		cas a;
		void settile();
		
		IA * tizio;
	public:
		Motore(Griglia * gr = 0);
		void muovi(mossa m);
		void stampa();
		
		void settaTizio();
		void muoviTizio();
};

#endif

#ifndef _IA_
#define _IA_

#include "griglia.h"

class IA
{
	private:
		Griglia *p;
	
	public:
		IA();
		float val(Griglia *g);
		float media(Griglia *g);
		mossa bestmove();
		void settagriglia(Griglia *gr);
};

#endif

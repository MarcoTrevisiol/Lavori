#include "ia.h"

IA::IA()
{
	p = 0;
	settagriglia(0);
}

void IA::settagriglia(Griglia * gr)
{
	if (p!=0) delete p;
	if (gr==0)
	{
		p = new Griglia;
	}
	else
		p = gr;
}

float IA::val(Griglia * g)
{
	if (g==0) return 0;
	int c = 0;
	unsigned i,j;
	for (i=0; i<dim; i++)
		for (j=0; j<dim; j++)
			if (g->exs(i,j)==0)
				c++;
	return c;
}


#include "motore.h"
#include <iostream>

Motore::Motore(Griglia * gr)
{
	if (gr)
		g = gr;
		else
		g = new Griglia;
	settile();
	g->add(a);
	settile();
	g->add(a);
}

void Motore::settile()
{
	do
	{
		a.x = rand()%dim;
		a.y = rand()%dim;
	} while (g->exs(a.x,a.y));
	a.c = rand()%5/4+1;
}

void Motore::muovi(mossa m)
{
	g->muovi(m);
	settile();
	g->add(a);
}

void Motore::stampa()
{
	int i,j;
	for (i=0; i<dim; i++)
	{
		for (j=0; j<dim; j++)
			cout<<g->exs(i,j)<<' ';
		cout<<'\n';
	}
}

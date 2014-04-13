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
	tizio = 0;
}

void Motore::settile()
{
	do
	{
		a.x = rand()%dim;
		a.y = rand()%dim;
	} while (g->exs(a.x,a.y));
	a.c = rand()%(prob1r2+1)/(prob1r2)+1;
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

void Motore::settaTizio()
{
	if (tizio!=0) delete tizio;
	tizio = new IA;
	tizio->settagriglia(g);
}

void Motore::muoviTizio()
{
	if (tizio==0) return;
	g->muovi(tizio->bestmove());
	settile();
	g->add(a);
}

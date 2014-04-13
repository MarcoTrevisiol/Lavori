#include "ia.h"
#include "motore.h"

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

float IA::media(Griglia *g)
{
	int i, j, caso=0;
	Griglia *q;
	cas C;
	float aver, som;
	for (i=0; i<dim; i++)
	{
		for (j=0; j<dim; j++)
		{
			if ((*p).exs(i,j)==0)
			{
				caso++;
				q=new Griglia(g);
				C.x=i;
				C.y=j;
				C.c=1;
				(*q).add(C);
				som+=val(q)*(prob1r2);
				C.c=2;
				(*q).add(C);
				som+=val(q);
				delete q;
			}

		}
	}
	
	if (caso!=0) aver=som/caso;
	else aver=-10000;
	
	return aver;
}

mossa IA::bestmove()
{
	mossa best;
	float mb, m;

	Griglia *g;
	g=new Griglia(p);
	(*g).muovi(su);
	mb=media(g);
	best=su;
	delete g;
	
	g=new Griglia(p);
	(*g).muovi(giu);
	m=media(g);
	if (m>mb)
	{
		mb=m;
		best=giu;
	}
	delete g;
	
	g=new Griglia(p);
	(*g).muovi(dx);
	m=media(g);
	if (m>mb)
	{
		mb=m;
		best=dx;
	}
	delete g;
	
	g=new Griglia(p);
	(*g).muovi(sx);
	m=media(g);
	if (m>mb)
	{
		mb=m;
		best=sx;
	}
	delete g;
	
	return best;
}



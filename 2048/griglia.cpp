#include "griglia.h"

Griglia::Griglia()
{
	int i,j;
	for (i=0; i<dim; i++)
	{
		for (j=0; j<dim; j++)
		{
			gri[i][j]=0;
		}
	}
	ladd.x=0;
	ladd.y=0;
	ladd.c=0;
}

unsigned sc(unsigned x, bool s)
{
	if (s) return x;
		else return dim-x-1;
}
		
void Griglia::muovi(mossa m)
{
	int i, j, k, h;
	switch (m)
	{
		case su: 
		case giu: 
			for (i=0; i<dim; i++)
			{
				k=0;
				for (j=0; j<dim; j++)
				{
					if (gri[sc(j,m==su)][i]!=0)
					{
						for (h=j+1; h<dim && gri[sc(h,m==su)][i]==0; h++);
						if (h<dim)
							if (gri[sc(j,m==su)][i]==gri[sc(h,m==su)][i])
							{
								gri[sc(j,m==su)][i]++;
								gri[sc(h,m==su)][i]=0;
							}
						gri[sc(k,m==su)][i]=gri[sc(j,m==su)][i];
						if (k!=j) gri[sc(j,m==su)][i]=0;
						k++;
					}
					
				}
			}
			break;
			
			
		case dx:
		case sx: 
		for (i=0; i<dim; i++)
			{
				k=0;
				for (j=0; j<dim; j++)
				{
					if (gri[i][sc(j,m==sx)]!=0)
					{
						for (h=j+1; h<dim && gri[i][sc(h,m==sx)]==0; h++);
						if (h<dim)
							if (gri[i][sc(j,m==sx)]==gri[i][sc(h,m==sx)])
							{
								gri[i][sc(j,m==sx)]++;
								gri[i][sc(h,m==sx)]=0;
							}
						gri[i][sc(k,m==sx)]=gri[i][sc(j,m==sx)];
						if (k!=j) gri[i][sc(j,m==sx)]=0;
						k++;
					}
					
				}
			}
			break;
	}
}

void Griglia::add(cas a)
{
	if (gri[a.x][a.y]==0)
	{
		gri[a.x][a.y]=a.c;
		ladd.c=a.c;
		ladd.x=a.x;
		ladd.y=a.y;
	}
}

cas Griglia::mostraagg()
{
	return ladd;
}

int Griglia::exs(unsigned x, unsigned y)
{
	return gri[x][y];
}

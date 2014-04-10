#ifndef _GRIGLIA_
#define _GRIGLIA_

#define dim 4

 enum mossa {giu, su, dx, sx};

struct cas
{
	unsigned x, y, c;
};

class Griglia
{
	protected:
		unsigned gri[dim][dim];
		cas ladd;
	public:
		Griglia();
		void muovi(mossa m);
		void add(cas a);
		cas mostraagg();
		int exs(unsigned x, unsigned y);
};




#endif

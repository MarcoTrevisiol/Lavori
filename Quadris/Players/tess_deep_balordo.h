#ifndef TESS_DEEP_H
#define TESS_DEEP_H

#include "ivplayer.h"
#include "tess_greedy.h"

#define DV  8

class Nodo
{
private:
    Partita::t_p ***cubo;
    float *val;
    unsigned count[DV];
    void Count();
    float LEval();
    unsigned depth;
    bool m_o;

public:
    Nodo(Partita::t_p ***cb, float* v, unsigned dep, bool is_m);
    ~Nodo();
    Nodo* genera(unsigned x, unsigned y, unsigned z);
    float Eval();
    bool M_o();
};

class Tess_Deep : public IVPlayer
{
private:
    Partita::t_p ***cubo;
    float val[DV];

    unsigned depth;
	std::list<my_p> buone;

public:
    Tess_Deep(bool r_o, Partita* p = 0);
    virtual void Play(unsigned& x, unsigned& y, unsigned& z);
    virtual void SetPartita(Partita* p);
};


#endif // TESS_DEEP_H

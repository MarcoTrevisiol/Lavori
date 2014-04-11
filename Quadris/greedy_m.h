#ifndef GREEDY_M_H
#define GREEDY_M_H

#include "tess_greedy.h"


class greedy_m : public Tess_Greedy
{
private:
    float wk;
public:
    greedy_m(bool r_o, float weak=0, Partita* p = 0);
    virtual void Play(unsigned& x, unsigned& y, unsigned& z);
};

#endif // GREEDY_M_H

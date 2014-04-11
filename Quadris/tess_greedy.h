#ifndef TESS_GREEDY_H
#define TESS_GREEDY_H

#include "ivplayer.h"
#include <fstream>
#include <list>

struct my_p
{
    unsigned x,y,z;
    my_p(unsigned, unsigned, unsigned);
};

class Tess_Greedy : public IVPlayer
{
protected:
    Partita::t_p cubo[D][D][D]; //tiene i valori del cubo

    float val[7];               //tiene i valori di allineamenti con 1, 2 e 3 dei propri che siano completabili
                                // e altrettanti per il nemico
    unsigned count[7];          //tiene il conteggio di tali allineamenti

    void Count();               //conta tali allineamenti
    float Eval();               //valuta i conteggi fatti

    std::list<my_p> buone;
public:
    Tess_Greedy(bool r_o, Partita* p = 0);
    virtual void Play(unsigned& x, unsigned& y, unsigned& z);
    virtual void SetPartita(Partita* p);
};

#endif // TESS_GREEDY_H

#ifndef CASUALE_H
#define CASUALE_H

#include "ivplayer.h"

class Casuale : public IVPlayer
{
public:
    Casuale(bool r_o, Partita* p = 0);
    virtual void Play(unsigned& x, unsigned& y, unsigned& z);
    virtual void SetPartita(Partita* p);
};

#endif // CASUALE_H

#include "casuale.h"

Casuale::Casuale(bool r_o, Partita* p)
    :IVPlayer(r_o, p)
{
}


void Casuale::Play(unsigned& x, unsigned& y, unsigned& z)
{
    do
    {
        x = rand()%D;
        y = rand()%D;
        z = rand()%D;
    }
    while (partita->get(x,y,z)!=Partita::nul);
}

void Casuale::SetPartita(Partita* p)
{
    IVPlayer::SetPartita(p);
}

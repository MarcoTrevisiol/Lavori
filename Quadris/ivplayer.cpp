#include "ivplayer.h"


IVPlayer::IVPlayer(bool r_o, Partita* p)
{
    partita = p;
    m_o = r_o;
}


void IVPlayer::Play(unsigned& x,unsigned& y, unsigned& z)
{

}

void IVPlayer::SetPartita(Partita* p)
{
    partita = p;
}

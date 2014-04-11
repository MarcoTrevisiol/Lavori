#ifndef IVPLAYER_H
#define IVPLAYER_H

#include "partita.h"

/*
  Questa classe definisce l'interfaccia di un giocatore virtuale
  Per creare un nuovo giocatore è sufficiente scrivere

  class Nome_del_Giocatore : public IVPlayer

  e inserirvi tutto il necessario.

  Importante: il costruttore deve ricevere la partita,
              la funzione Play deve essere riscritta.
  */

class IVPlayer
{
public:
    IVPlayer(bool r_o = true, Partita* p = 0);
        //il costruttore riceve come parametro se gioca in qualità di o
        //e la partita su cui deve giocare

    virtual void Play(unsigned&,unsigned&, unsigned&);
        //questa è la funzione che deve essere sovrascritta e l'unica a venire chiamata

    virtual void SetPartita(Partita* p);

protected:
    Partita* partita;
    bool m_o;
};

#endif // IVPLAYER_H

#ifndef PARTITA_H
#define PARTITA_H

#define D   4
#define u   unsigned
#include <cstdlib>

/*
  Questa classe definisce gli elementi necessari per la partita
  */
class Partita
{
public:
    Partita(bool is_o_turn);
        //costruttore

    enum t_p {nul, op, xp, oxp};
        //tipi che indicano i segnalini:
        //vuoto-nessuno: nul
        //giocatore o: op
        //giocatore x: xp
        //patta (per l'esito): oxp

    t_p esito();
        //fornisce il vincitore della partita

    bool Is_o();
        //dice a chi tocca muovere

    t_p get(u,u,u);
        //fornisce il segnalino posto nella casella indicata dalle coordinate

    void last(u&, u&, u&);
        //fornisce l'ultima mossa effettuata

protected:
    void segna(u,u,u);
    void getAll(u*&, u*&, u*&);

private:
    t_p cas[D][D][D];
    bool o_turn;
    u xl,yl,zl;

    u sec,var,fc,sc;

    bool check(t_p);
};


/*
  Questa classe permette di mettere i segnalini sul campo di gioco
  */
class WPartita : public Partita
{
public:
    WPartita(bool is_o_turn);
    void Segna(u,u,u);
    bool GetAll(u*&, u*&, u*&);
};



#endif // PARTITA_H

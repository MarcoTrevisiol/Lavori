#ifndef TESS_DEEP_H
#define TESS_DEEP_H

#include "ivplayer.h"
#include <vector>
#include <list>

#define DV	8										//dimensione del vettore valori
#define MP	20										//Massima Profondità valutata

struct t_pos
{
	u x,y,z;
	t_pos(u x_=0, u y_=0, u z_=0);
};

class Tess_Deep : public IVPlayer
{
private:
	Partita::t_p conf[MP][D][D][D];					//ad ogni indice c'è la configurazione di quella profondità
    u short depth;									//profondità valutata = quante mosse prevedere => depth>0 e l<=depth
    bool m_o;										//sono il giocatore O?

    u count[DV];
    void Count(u l);								//conta gli allineamenti parziali e li pone in count
	std::list<t_pos> b3, c3;						//se ce ne sono 3 in fila qui viene messo il 4; Buone e Cattive
	
    float val[DV];									//contiene i valori del singolo allineamento parziale
    float LEval(u l);								//valuta localmente una configurazione
													//la valutazione fornisce il valore atteso dal giocatore Tess_Deep,
													//non da chi muove al livello l
													
	void translate(u l, u x, u y, u z);				//transla il contenuto della conf[l] in conf[l+1] con la mossa in (x,y,z)
	float Eval(u l);								//valuta in profondità; stesso discorso di cui sopra
	
	std::list<t_pos> buone;							//contiene le mosse giudicate migliori da giocare

    bool progressivo;                               //permette di evitare onerose ricerche all'inizio
    u short max_depth;
    u short yinc;

public:
    Tess_Deep(bool r_o, u short d = 1, bool prog = false, Partita* p = 0);
    virtual void Play(u& x, u& y, u& z);
    virtual void SetPartita(Partita* p);
};


#endif // TESS_DEEP_H

#ifndef WIDPAR_H
#define WIDPAR_H

#include <QWidget>
#include "partita.h"
#include "my_button.h"
#include <QLabel>
#include <QTimer>
#include "ivplayer.h"
#include <list>
#include <fstream>

#define VPlayerL    5

struct t_player
{
    bool is_h;
    IVPlayer* vplayer;
    t_player(bool h = true, IVPlayer* p = 0);
};

struct t_move
{
    uint x,y,z;
};
typedef std::list<t_move> t_savp;


class WidPar : public QWidget
{
    Q_OBJECT
public:
    explicit WidPar(QWidget *parent = 0);
    void setOpl(t_player);
    void setXpl(t_player);

signals:
    void fdp();
    void is_vpt(int);

public slots:
    void Segna(uint,uint,uint);
    void NewP();
    void VPlay();
    void SetPartSav(t_savp);
    void StartPlaySav(bool);
    void PlaySav();
    void SetT(int);

private:
    WPartita* partita;
    My_Button* cells[D][D][D];
    u cells_w, cells_s, top_marg;
    QLabel *l_ply, *l_op, *l_xp;

    t_player Opl, Xpl;

    QTimer* tim;
    t_savp savp;
    std::list<t_move>::iterator itp;
    bool is_s,eop;
    int T;

    std::ofstream psav;
};

#endif // WIDPAR_H

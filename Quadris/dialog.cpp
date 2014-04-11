#include "dialog.h"
#include "ui_dialog.h"
#include <fstream>
#include <QFileDialog>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent, Qt::Window | Qt::WindowCloseButtonHint),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QStringList ls;
    ls<<"Umano"<<"Casuale"<<"Tess_Greedy"<<"Scarso"<<"Pippa"<<"Superf"<<"2 depth"<<"3 depth"<<"4 depth";
    ls<<"Progressivo";
    types_p.setStringList(ls);
    ui->combo_opl->setModel(&types_p);
    ui->combo_opl->setCurrentIndex(0);
    ui->combo_xpl->setModel(&types_p);
    ui->combo_xpl->setCurrentIndex(0);
    ui->horizontalSlider->setValue(10);
    ui->Wid_Partita_2->SetT(10);

    connect(ui->button_newgame,SIGNAL(released()),
            ui->Wid_Partita,SLOT(NewP()));
    connect(ui->combo_opl,SIGNAL(activated(int)),
            SLOT(SetOP(int)));
    connect(ui->combo_xpl,SIGNAL(activated(int)),
            SLOT(SetXP(int)));

    connect(ui->button_carica,SIGNAL(clicked()),
            SLOT(Carica()));
    connect(ui->button_next,SIGNAL(clicked()),
            SLOT(Next()));
    connect(ui->button_prev,SIGNAL(clicked()),
            SLOT(Prev()));
    connect(ui->button_play,SIGNAL(clicked(bool)),
            ui->Wid_Partita_2,SLOT(StartPlaySav(bool)));
    connect(ui->Wid_Partita_2,SIGNAL(fdp()),
            SLOT(FdpSav()));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),
            ui->Wid_Partita_2,SLOT(SetT(int)));
}

Dialog::~Dialog()
{
    delete ui;
}

IVPlayer* Dialog::newPlayer(int i, bool r_o)
{
    IVPlayer* pl;
    switch(i)
    {
    case(1):
        pl = new Casuale(r_o);
        break;
    case(2):
        pl = new Tess_Greedy(r_o);
        break;
    case(3):
        pl = new greedy_m(r_o, 0.3);
        break;
    case(4):
        pl = new greedy_m(r_o, 0.7);
        break;
    case(5):
    case(6):
    case(7):
    case(8):
        pl = new Tess_Deep(r_o, i-4);
        break;
    case(9):
        pl = new Tess_Deep(r_o, 4, true);
        break;
    default:
        pl = 0;
    }
    return pl;
}

void Dialog::SetOP(int i)
{
    t_player pl;
    pl.vplayer = newPlayer(i, true);
    pl.is_h = !pl.vplayer;
    ui->Wid_Partita->setOpl(pl);
}

void Dialog::SetXP(int i)
{
    t_player pl;
    pl.vplayer = newPlayer(i, false);
    pl.is_h = !pl.vplayer;
    ui->Wid_Partita->setXpl(pl);
}

void conv(char *n, t_move& m)
{
    char c;
    c = n[0];
    m.x = atoi(&c);
    c = n[1];
    m.y = atoi(&c);
    c = n[2];
    m.z = atoi(&c);
}

void Dialog::Carica()
{
    QString str = QFileDialog::getOpenFileName(this,
                      tr("Scegli elenco partite"),
                      "...", tr("Elenchi partite (*)"));
    QByteArray qba = str.toLocal8Bit();
    std::ifstream inp(qba.data());
    t_move m;
    char* c = new char[50];
    cur_p.clear();
    while (!inp.eof())
    {
        inp>>c;
        cur_p.push_back(t_savp());
        while (strcmp(c,";"))
        {
            conv(c,m);
            cur_p.back().push_back(m);
            inp>>c;
        }
    }
    cur_p.reverse();
    cur_p.erase(cur_p.begin());
    itc = cur_p.begin();
    inp.close();
    ui->button_prev->setEnabled(false);
    ui->button_play->setEnabled(true);
    ui->button_next->setEnabled(true);
    if (itc == cur_p.end())
    {
        ui->button_next->setEnabled(false);
        ui->button_play->setEnabled(false);
    }
    itc++;
    if (itc == cur_p.end())
    {
        ui->button_next->setEnabled(false);
    }
    itc = cur_p.begin();
    ui->Wid_Partita_2->SetPartSav(*itc);
}

void Dialog::Next()
{
    ui->button_prev->setEnabled(true);
    itc++;
    itc++;
    if (itc == cur_p.end())
    {
        ui->button_next->setEnabled(false);
    }
    itc--;
    ui->Wid_Partita_2->SetPartSav(*itc);
}

void Dialog::Prev()
{
    ui->button_next->setEnabled(true);
    itc--;
    if (itc == cur_p.begin())
    {
        ui->button_prev->setEnabled(false);
    }
    ui->Wid_Partita_2->SetPartSav(*itc);
}

void Dialog::FdpSav()
{
    ui->button_play->setChecked(false);
}

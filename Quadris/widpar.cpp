#include "widpar.h"
#include "QMessageBox"

t_player::t_player(bool h, IVPlayer* p)
{
    is_h = h;
    vplayer = p;
}

WidPar::WidPar(QWidget *parent) :
    QWidget(parent)
{
    partita = new WPartita(true);

    tim = new QTimer(this);
    connect(tim,SIGNAL(timeout()),SLOT(VPlay()));
    connect(tim,SIGNAL(timeout()),tim,SLOT(stop()));
    connect(this,SIGNAL(is_vpt(int)),tim,SLOT(start(int)));

    setOpl(t_player());
    setXpl(t_player());
    cells_w = 30;
    cells_s = 32;
    top_marg = 40;
    u x,y,z;
    for (x=0; x<D; x++)
        for (y=0; y<D; y++)
            for (z=0; z<D; z++)
            {
                cells[x][y][z]=new My_Button(x,y,z,this);
                cells[x][y][z]->setGeometry(x*(4*cells_w+cells_s)+y*cells_w,z*cells_w+top_marg,cells_w,cells_w);
                connect(cells[x][y][z],SIGNAL(Cliced(uint,uint,uint)),SLOT(Segna(uint,uint,uint)));

            }
    l_ply = new QLabel(this);
    l_ply->setText("Giocatore corrente: ");
    l_ply->setGeometry(8,5,130,25);
    l_op = new QLabel(this);
    l_op->setPixmap(QPixmap(":/icons/o_player.png"));
    l_op->setGeometry(140,5,25,25);
    l_xp = new QLabel(this);
    l_xp->setPixmap(QPixmap(":/icons/x_player.png"));
    l_xp->setGeometry(175,5,25,25);
    l_xp->setEnabled(false);
    is_s=false;
    eop=false;
    psav.open("partite_salvate", std::ofstream::out | std::ofstream::app);
    T = VPlayerL;
}


void WidPar::Segna(u x,u y,u z)
{
    if (x>=D||y>=D||z>=D)
    {
        emit is_vpt(VPlayerL);
        return;
    }
    if (!cells[x][y][z]->icon().isNull())
        return;
    if (partita->Is_o())
        cells[x][y][z]->setIcon(QIcon(":/icons/o_player.png"));
    else cells[x][y][z]->setIcon(QIcon(":/icons/x_player.png"));
    partita->Segna(x,y,z);
    psav<<x<<y<<z<<' ';
    l_op->setEnabled(partita->Is_o());
    l_xp->setEnabled(!partita->Is_o());
    Partita::t_p es = partita->esito();
    if (es!=Partita::nul)
    {
        u *xs, *ys, *zs;
        xs = ys = zs = 0;
        if (partita->GetAll(xs,ys,zs))
            for (u i=0; i<D; i++)
                cells[xs[i]][ys[i]][zs[i]]->Evid(true);
        QMessageBox msg;
        QString tex;
        switch(es)
        {
        case(Partita::op):
            tex = "Vince il giocatore O";
            break;
        case(Partita::xp):
            tex = "Vince il giocatore X";
            break;
        case(Partita::oxp):
            tex = "Patta!";
            break;
        default:
            break;
        }
        msg.setText(tex);
        msg.exec();
        emit fdp();
        tim->stop();
        psav<<";\n";
        psav.close();
    }
    else
    {
        emit is_vpt(VPlayerL);
    }
}

void WidPar::NewP()
{
    u x,y,z;
    for (x=0; x<D; x++)
        for (y=0; y<D; y++)
            for (z=0; z<D; z++)
            {
                cells[x][y][z]->setIcon(QIcon());
                cells[x][y][z]->Evid(false);
            }
    delete partita;
    partita = new WPartita(true);
    if (!Opl.is_h)
        Opl.vplayer->SetPartita(partita);
    if (!Xpl.is_h)
        Xpl.vplayer->SetPartita(partita);

    l_op->setEnabled(partita->Is_o());
    l_xp->setEnabled(!partita->Is_o());

    if (!psav.is_open())
        psav.open("partite_salvate", std::ofstream::out | std::ofstream::app);

    emit is_vpt(VPlayerL);
}

void WidPar::setOpl(t_player p)
{
    Opl.is_h = p.is_h;
    Opl.vplayer = p.vplayer;
    if (!Opl.is_h)
    {
        Opl.vplayer->SetPartita(partita);
        if (!Xpl.is_h)
            disconnect(tim,SIGNAL(timeout()),tim,SLOT(stop()));
    }
    else connect(tim,SIGNAL(timeout()),tim,SLOT(stop()));
}

void WidPar::setXpl(t_player p)
{
    Xpl.is_h = p.is_h;
    Xpl.vplayer = p.vplayer;
    if (!Xpl.is_h)
    {
        Xpl.vplayer->SetPartita(partita);
        if (!Opl.is_h)
            disconnect(tim,SIGNAL(timeout()),tim,SLOT(stop()));
    }
    else connect(tim,SIGNAL(timeout()),tim,SLOT(stop()));
}

void WidPar::VPlay()
{
    unsigned x,y,z;
    if (partita->Is_o()&&!Opl.is_h)
    {
        Opl.vplayer->Play(x,y,z);
        Segna(x,y,z);
        return;
    }
    if (!partita->Is_o()&&!Xpl.is_h)
    {
        Xpl.vplayer->Play(x,y,z);
        Segna(x,y,z);
    }
}

void WidPar::SetPartSav(t_savp p)
{
    eop = false;
    savp = p;
    itp = savp.begin();
    if (!is_s)
    {
        disconnect(tim,SIGNAL(timeout()),this,SLOT(VPlay()));
        disconnect(tim,SIGNAL(timeout()),tim,SLOT(stop()));
        connect(tim,SIGNAL(timeout()),SLOT(PlaySav()));
        is_s=true;
    }
    u x,y,z;
    for (x=0; x<D; x++)
        for (y=0; y<D; y++)
            for (z=0; z<D; z++)
            {
                cells[x][y][z]->setIcon(QIcon());
                cells[x][y][z]->Evid(false);
            }
    delete partita;
    partita = new WPartita(true);
}

void WidPar::StartPlaySav(bool htg)
{
    if (htg)
    {
        if (eop)
            SetPartSav(savp);
        tim->start(T);
    }
    else tim->stop();
}

void WidPar::PlaySav()
{
    if (itp!=savp.end())
    {
        if (!cells[itp->x][itp->y][itp->z]->icon().isNull())
            return;
        if (partita->Is_o())
            cells[itp->x][itp->y][itp->z]->setIcon(QIcon(":/icons/o_player.png"));
        else cells[itp->x][itp->y][itp->z]->setIcon(QIcon(":/icons/x_player.png"));
        partita->Segna(itp->x,itp->y,itp->z);
        l_op->setEnabled(partita->Is_o());
        l_xp->setEnabled(!partita->Is_o());
        itp++;
    }
    else
    {
        tim->stop();
        emit fdp();
        itp = savp.begin();
        Partita::t_p es = partita->esito();
        if (es!=Partita::nul)
        {
            u *xs, *ys, *zs;
            xs = ys = zs = 0;
            if (partita->GetAll(xs,ys,zs))
                for (u i=0; i<D; i++)
                    cells[xs[i]][ys[i]][zs[i]]->Evid(true);
            QMessageBox msg;
            QString tex;
            switch(es)
            {
            case(Partita::op):
                tex = "Vince il giocatore O";
                break;
            case(Partita::xp):
                tex = "Vince il giocatore X";
                break;
            case(Partita::oxp):
                tex = "Patta!";
                break;
            default:
                break;
            }
            msg.setText(tex);
            msg.exec();
            emit fdp();
            tim->stop();
        }
        eop = true;
    }

}

void WidPar::SetT(int t)
{
    T = 2000-t*19;
}

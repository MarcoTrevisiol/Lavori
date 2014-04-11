#include "partita.h"
#include <fstream>

Partita::Partita(bool is_o_turn)
{
    o_turn = is_o_turn;
    xl = yl = zl = D;
    u i,j,k;
    for (i=0; i<D; i++)
        for (j=0; j<D; j++)
            for(k=0; k<D; k++)
                cas[i][j][k] = nul;
}

bool Partita::Is_o()
{
    return o_turn;
}

void Partita::segna(u a, u b, u c)
{
    if (a<D && b<D && c<D)
    {
        cas[a][b][c] = o_turn?op:xp;
        o_turn = !o_turn;
        xl = a;
        yl = b;
        zl = c;
    }
}

Partita::t_p Partita::get(u x,u y,u z)
{
    if (x<D)
        if (y<D)
            if (z<D)
                return cas[x][y][z];
    return nul;
}

void Partita::last(u& a, u& b, u& c)
{
    a = xl;
    b = yl;
    c = zl;
}

Partita::t_p Partita::esito()
{
    if (check(op)) return op;
    if (check(xp)) return xp;
    u x,y,z;
    for (x=0; x<D; x++)
        for (y=0; y<D; y++)
            for (z=0; z<D; z++)
            {
                if(cas[x][y][z]==nul)
                    return nul;
            }
    return oxp;
}


bool Partita::check(t_p t)
{
    u x,y,z;
    for (x=0; x<D; x++)
        for (y=0; y<D; y++)
        {
            for (z=0; z<D&&cas[x][y][z]==t; z++){}
            if (z==D)
            {
                sec = 1;
                var = 1;
                fc = x;
                sc = y;
                return true;
            }
            for (z=0; z<D&&cas[x][z][y]==t; z++){}
            if (z==D)
            {
                sec = 1;
                var = 2;
                fc = x;
                sc = y;
                return true;
            }
            for (z=0; z<D&&cas[z][x][y]==t; z++){}
            if (z==D)
            {
                sec = 1;
                var = 3;
                fc = x;
                sc = y;
                return true;
            }
        }
    for (x=0; x<D; x++)
    {
        for (z=0; z<D&&cas[x][z][z]==t; z++){}
        if (z==D)
        {
            sec = 2;
            var = 1;
            fc = x;
            return true;
        }
        for (z=0; z<D&&cas[x][z][D-z-1]==t; z++){}
        if (z==D)
        {
            sec = 2;
            var = 2;
            fc = x;
            return true;
        }

        for (z=0; z<D&&cas[z][x][z]==t; z++){}
        if (z==D)
        {
            sec = 2;
            var = 3;
            fc = x;
            return true;
        }
        for (z=0; z<D&&cas[z][x][D-z-1]==t; z++){}
        if (z==D)
        {
            sec = 2;
            var = 4;
            fc = x;
            return true;
        }

        for (z=0; z<D&&cas[z][z][x]==t; z++){}
        if (z==D)
        {
            sec = 2;
            var = 5;
            fc = x;
            return true;
        }
        for (z=0; z<D&&cas[z][D-z-1][x]==t; z++){}
        if (z==D)
        {
            sec = 2;
            var = 6;
            fc = x;
            return true;
        }
    }
    for (z=0; z<D&&cas[z][z][z]==t; z++){}
    if (z==D)
    {
        sec = 3;
        var = 1;
        return true;
    }
    for (z=0; z<D&&cas[z][D-z-1][z]==t; z++){}
    if (z==D)
    {
        sec = 3;
        var = 2;
        return true;
    }
    for (z=0; z<D&&cas[z][z][D-z-1]==t; z++){}
    if (z==D)
    {
        sec = 3;
        var = 3;
        return true;
    }
    for (z=0; z<D&&cas[z][D-z-1][D-z-1]==t; z++){}
    if (z==D)
    {
        sec = 3;
        var = 4;
        return true;
    }
    return false;
}

void Partita::getAll(u* &xs, u* &ys, u* &zs)
{
    if (!check(op)&&!check(xp))
    {
        xs = ys = zs = 0;
        return;
    }
    xs = new u[D];
    ys = new u[D];
    zs = new u[D];
    u z;
    switch(sec)
    {
    case(1):
        switch(var)
        {
        case(1):
            for (z=0; z<D; z++)
            {
                xs[z] = fc;
                ys[z] = sc;
                zs[z] = z;
            }
            return;
        case(2):
            for (z=0; z<D; z++)
            {
                xs[z] = fc;
                ys[z] = z;
                zs[z] = sc;
            }
            return;
        case(3):
            for (z=0; z<D; z++)
            {
                xs[z] = z;
                ys[z] = fc;
                zs[z] = sc;
            }
            return;
        default:
            xs = ys = zs = 0;
            return;
        }
    case(2):
        switch(var)
        {
        case(1):
            for (z=0; z<D; z++)
            {
                xs[z] = fc;
                ys[z] = z;
                zs[z] = z;
            }
            return;
        case(2):
            for (z=0; z<D; z++)
            {
                xs[z] = fc;
                ys[z] = z;
                zs[z] = D-1-z;
            }
            return;
        case(3):
            for (z=0; z<D; z++)
            {
                xs[z] = z;
                ys[z] = fc;
                zs[z] = z;
            }
            return;
        case(4):
            for (z=0; z<D; z++)
            {
                xs[z] = z;
                ys[z] = fc;
                zs[z] = D-1-z;
            }
            return;
        case(5):
            for (z=0; z<D; z++)
            {
                xs[z] = z;
                ys[z] = z;
                zs[z] = fc;
            }
            return;
        case(6):
            for (z=0; z<D; z++)
            {
                xs[z] = z;
                ys[z] = D-1-z;
                zs[z] = fc;
            }
            return;
        default:
            xs = ys = zs = 0;
            return;
        }
    case(3):
        switch(var)
        {
        case(1):
            for (z=0; z<D; z++)
            {
                xs[z] = z;
                ys[z] = z;
                zs[z] = z;
            }
            return;
        case(2):
            for (z=0; z<D; z++)
            {
                xs[z] = z;
                ys[z] = D-1-z;
                zs[z] = z;
            }
            return;
        case(3):
            for (z=0; z<D; z++)
            {
                xs[z] = z;
                ys[z] = z;
                zs[z] = D-1-z;
            }
            return;
        case(4):
            for (z=0; z<D; z++)
            {
                xs[z] = z;
                ys[z] = D-1-z;
                zs[z] = D-1-z;
            }
            return;
        default:
            xs = ys = zs = 0;
            return;
        }
    default:
        xs = ys = zs = 0;
        return;
    }
}


WPartita::WPartita(bool is_o_turn)
    :Partita(is_o_turn)
{
}

void WPartita::Segna(u x,u y,u z)
{
    segna(x,y,z);
}

bool WPartita::GetAll(u* &xs, u* &ys, u* &zs)
{
    getAll(xs,ys,zs);
    return (xs!=0);
}


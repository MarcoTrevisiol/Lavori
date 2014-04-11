#include "tess_greedy.h"

my_p::my_p(unsigned a, unsigned b, unsigned c)
    :x(a),y(b),z(c)
{
}

Tess_Greedy::Tess_Greedy(bool r_o, Partita* p)
    :IVPlayer(r_o, p)
{
    SetPartita(p);
    val[0] = 0.05;
    val[1] = 0.3;
    val[2] = 0.7;
    val[3] = 10;

    val[4] = -0.1;
    val[5] = -0.1;
    val[6] = -1;

    for (unsigned i=0; i<7; i++)
        count[i] = 0;
}

void Tess_Greedy::Play(unsigned& x, unsigned& y, unsigned& z)
{
    partita->last(x,y,z);
    cubo[x][y][z] = partita->get(x,y,z);
    float Max=-10;
    u a,b,c;
    for (a=0; a<D; a++)
        for (b=0; b<D; b++)
            for (c=0; c<D; c++)
            {
                if (cubo[a][b][c]==Partita::nul)
                {
                    cubo[a][b][c] = (m_o)?Partita::op:Partita::xp;
                    Count();
                    if (Eval()>Max)
                    {
                        buone.clear();
                        Max = Eval();
                        buone.push_back(my_p(a,b,c));
                    }
                    if (Eval()==Max)
                    {
                        buone.push_back(my_p(a,b,c));
                    }
                    cubo[a][b][c] = Partita::nul;
                }
            }

    a = rand()%buone.size();
    std::list<my_p>::iterator it;
    for (it=buone.begin(), b=0; b<a; b++, it++);
    x = it->x;
    y = it->y;
    z = it->z;
    //x = buone.front().x;
    //y = buone.front().y;
    //z = buone.front().z;

    cubo[x][y][z] = (m_o)?Partita::op:Partita::xp;
}

void Tess_Greedy::SetPartita(Partita* p)
{
    IVPlayer::SetPartita(p);
    u i,j,k;
    for (i=0; i<D; i++)
        for (j=0; j<D; j++)
            for (k=0; k<D; k++)
            {
                cubo[i][j][k] = (!p)?Partita::nul:p->get(i,j,k);
            }
}

void Tess_Greedy::Count()
{
    for (unsigned i=0; i<7; i++)
        count[i] = 0;

    u mi,ti;
    u x,y,z;
    for (x=0; x<D; x++)
        for (y=0; y<D; y++)
        {
            mi = ti = 0;
            for (z=0; z<D; z++)
            {
                switch (cubo[x][y][z])
                {
                case (Partita::op):
                    (m_o)?mi++:ti++;
                    break;
                case(Partita::xp):
                    (m_o)?ti++:mi++;
                    break;
                default:break;
                }
            }
            if (ti==0 && mi>0 && mi<5)
                count[mi-1]++;
            if (mi==0 && ti>0 && ti<4)
                count[ti+3]++;


            mi = ti = 0;
            for (z=0; z<D; z++)
            {
                switch (cubo[x][z][y])
                {
                case (Partita::op):
                    (m_o)?mi++:ti++;
                    break;
                case(Partita::xp):
                    (m_o)?ti++:mi++;
                    break;
                    default:break;
                }
            }
            if (ti==0 && mi>0 && mi<5)
                count[mi-1]++;
            if (mi==0 && ti>0 && ti<4)
                count[ti+3]++;

            mi = ti = 0;
            for (z=0; z<D; z++)
            {
                switch (cubo[z][x][y])
                {
                case (Partita::op):
                    (m_o)?mi++:ti++;
                    break;
                case(Partita::xp):
                    (m_o)?ti++:mi++;
                    break;
                    default:break;
                }
            }
            if (ti==0 && mi>0 && mi<5)
                count[mi-1]++;
            if (mi==0 && ti>0 && ti<4)
                count[ti+3]++;

        }
    for (x=0; x<D; x++)
    {

        mi = ti = 0;
        for (z=0; z<D; z++)
        {
            switch (cubo[x][z][z])
            {
            case (Partita::op):
                (m_o)?mi++:ti++;
                break;
            case(Partita::xp):
                (m_o)?ti++:mi++;
                break;
                default:break;
            }
        }
        if (ti==0 && mi>0 && mi<5)
            count[mi-1]++;
        if (mi==0 && ti>0 && ti<4)
            count[ti+3]++;

        mi = ti = 0;
        for (z=0; z<D; z++)
        {
            switch (cubo[x][z][D-z-1])
            {
            case (Partita::op):
                (m_o)?mi++:ti++;
                break;
            case(Partita::xp):
                (m_o)?ti++:mi++;
                break;
                default:break;
            }
        }
        if (ti==0 && mi>0 && mi<5)
            count[mi-1]++;
        if (mi==0 && ti>0 && ti<4)
            count[ti+3]++;

        mi = ti = 0;
        for (z=0; z<D; z++)
        {
            switch (cubo[z][x][z])
            {
            case (Partita::op):
                (m_o)?mi++:ti++;
                break;
            case(Partita::xp):
                (m_o)?ti++:mi++;
                break;
                default:break;
            }
        }
        if (ti==0 && mi>0 && mi<5)
            count[mi-1]++;
        if (mi==0 && ti>0 && ti<4)
            count[ti+3]++;

        mi = ti = 0;
        for (z=0; z<D; z++)
        {
            switch (cubo[z][x][D-z-1])
            {
            case (Partita::op):
                (m_o)?mi++:ti++;
                break;
            case(Partita::xp):
                (m_o)?ti++:mi++;
                break;
                default:break;
            }
        }
        if (ti==0 && mi>0 && mi<5)
            count[mi-1]++;
        if (mi==0 && ti>0 && ti<4)
            count[ti+3]++;

        mi = ti = 0;
        for (z=0; z<D; z++)
        {
            switch (cubo[z][z][x])
            {
            case (Partita::op):
                (m_o)?mi++:ti++;
                break;
            case(Partita::xp):
                (m_o)?ti++:mi++;
                break;
                default:break;
            }
        }
        if (ti==0 && mi>0 && mi<5)
            count[mi-1]++;
        if (mi==0 && ti>0 && ti<4)
            count[ti+3]++;

        mi = ti = 0;
        for (z=0; z<D; z++)
        {
            switch (cubo[z][D-z-1][x])
            {
            case (Partita::op):
                (m_o)?mi++:ti++;
                break;
            case(Partita::xp):
                (m_o)?ti++:mi++;
                break;
                default:break;
            }
        }
        if (ti==0 && mi>0 && mi<5)
            count[mi-1]++;
        if (mi==0 && ti>0 && ti<4)
            count[ti+3]++;

    }

    mi = ti = 0;
    for (z=0; z<D; z++)
    {
        switch (cubo[z][z][z])
        {
        case (Partita::op):
            (m_o)?mi++:ti++;
            break;
        case(Partita::xp):
            (m_o)?ti++:mi++;
            break;
            default:break;
        }
    }
    if (ti==0 && mi>0 && mi<5)
        count[mi-1]++;
    if (mi==0 && ti>0 && ti<4)
        count[ti+3]++;

    mi = ti = 0;
    for (z=0; z<D; z++)
    {
        switch (cubo[z][D-z-1][z])
        {
        case (Partita::op):
            (m_o)?mi++:ti++;
            break;
        case(Partita::xp):
            (m_o)?ti++:mi++;
            break;
            default:break;
        }
    }
    if (ti==0 && mi>0 && mi<5)
        count[mi-1]++;
    if (mi==0 && ti>0 && ti<4)
        count[ti+3]++;

    mi = ti = 0;
    for (z=0; z<D; z++)
    {
        switch (cubo[z][z][D-z-1])
        {
        case (Partita::op):
            (m_o)?mi++:ti++;
            break;
        case(Partita::xp):
            (m_o)?ti++:mi++;
            break;
            default:break;
        }
    }
    if (ti==0 && mi>0 && mi<5)
        count[mi-1]++;
    if (mi==0 && ti>0 && ti<4)
        count[ti+3]++;

    mi = ti = 0;
    for (z=0; z<D; z++)
    {
        switch (cubo[z][D-z-1][D-z-1])
        {
        case (Partita::op):
            (m_o)?mi++:ti++;
            break;
        case(Partita::xp):
            (m_o)?ti++:mi++;
            break;
            default:break;
        }
    }
    if (ti==0 && mi>0 && mi<5)
        count[mi-1]++;
    if (mi==0 && ti>0 && ti<4)
        count[ti+3]++;
}

float Tess_Greedy::Eval()
{
    float ps = 0;
    for (u i=0; i<7; i++)
    {
        ps+=val[i]*count[i];
    }
    return ps;
}

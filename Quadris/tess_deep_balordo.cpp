#include "tess_deep.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

int ttt;

Nodo::Nodo(Partita::t_p ***cb, float* v, unsigned dep, bool is_m)
    :depth(dep),m_o(is_m)
{
    unsigned a,b,c;
    cubo = new Partita::t_p**[D];
    for (a=0; a<D; a++)
        cubo[a] = new Partita::t_p*[D];

    for (a=0; a<D; a++)
        for (b=0; b<D; b++)
            cubo[a][b] = new Partita::t_p[D];

    for (a=0; a<D; a++)
        for (b=0; b<D; b++)
            for (c=0; c<D; c++)
                cubo[a][b][c] = (!cb ? Partita::nul : cb[a][b][c]);
    if (!v)
    {
        val = new float[DV];
        for (uint a=0; a<DV; a++)
            val[a] = 0;
    }
    else val = v;
}

Nodo::~Nodo()
{
    unsigned a,b;
    for (a=0; a<D; a++)
        for (b=0; b<D; b++)
            delete cubo[a][b];
    for (a=0; a<D; a++)
        delete cubo[a];
    delete cubo;
}

bool Nodo::M_o()
{
    return m_o;
}

void Nodo::Count()
{
    for (unsigned i=0; i<DV; i++)
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
            if (mi==0 && ti>0 && ti<5)
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
            if (mi==0 && ti>0 && ti<5)
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
            if (mi==0 && ti>0 && ti<5)
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
        if (mi==0 && ti>0 && ti<5)
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
        if (mi==0 && ti>0 && ti<5)
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
        if (mi==0 && ti>0 && ti<5)
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
        if (mi==0 && ti>0 && ti<5)
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
        if (mi==0 && ti>0 && ti<5)
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
        if (mi==0 && ti>0 && ti<5)
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
    if (mi==0 && ti>0 && ti<5)
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
    if (mi==0 && ti>0 && ti<5)
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
    if (mi==0 && ti>0 && ti<5)
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
    if (mi==0 && ti>0 && ti<5)
        count[ti+3]++;
}


float Nodo::LEval()
{
    ttt++;
	Count();
    float ps = 0;
    for (u i=0; i<DV; i++)
        ps+=val[i]*count[i];
    if (!m_o) ps*=-1;
    return ps;
}

Nodo* Nodo::genera(unsigned x, unsigned y, unsigned z)
{
    if (depth==0) return 0;
    if (cubo[x][y][z]!=Partita::nul)
        return 0;

    Nodo* n = new Nodo(cubo,val,depth-1,!m_o);
    n->cubo[x][y][z] = (!m_o?Partita::op:Partita::xp);//qui bisogna considerare che genera serve per il livello soprastante!

    return n;
}

float Nodo::Eval()
{
    if (!depth)
        return LEval();
    Count();
    if (count[3]>0)
        return val[3];
    if (count[7]>0)
        return val[7];
    unsigned a,b,c;
    float max, m;
    if (m_o) max = -1000;
        else max = 1000;
    Nodo* n;
    for (a=0; a<D; a++)
        for (b=0; b<D; b++)
            for (c=0; c<D; c++)
            {
                n = genera(a,b,c);
                if (n)
                {
                    m = n->Eval();
                    if (m_o)
                    {
						if (m>max)
							max = m;
					}
					else if (m<max)
                            max = m;
                    delete n;
                }
            }
//    std::ofstream acca("creato",std::ofstream::out|std::ofstream::app);
//    acca<<"Eval  "<<ttt<<"\n";
//    acca.close();
    return max;
}

Tess_Deep::Tess_Deep(bool r_o, Partita* p)
    :IVPlayer(r_o, p)
{
    val[0] = 0.09;
    val[1] = 0.23;
    val[2] = 0.65;
    val[3] = 10;

    val[4] = -0.09;
    val[5] = -0.3;
    val[6] = -1;
    val[7] = -10;

    depth = 3;

    unsigned a,b;
    cubo = new Partita::t_p**[D];
    for (a=0; a<D; a++)
        cubo[a] = new Partita::t_p*[D];
    for (a=0; a<D; a++)
        for (b=0; b<D; b++)
            cubo[a][b] = new Partita::t_p[D];

    SetPartita(p);
//    std::ofstream acca("creato",std::ofstream::out|std::ofstream::app);
//    acca<<"creato giocatore "<<m_o<<"\n";
//    acca.close();
    ttt = 0;
}

void Tess_Deep::Play(unsigned& x, unsigned& y, unsigned& z)
{
    //std::ofstream acca("creato",std::ofstream::out|std::ofstream::app);
    //acca<<"play\n";
    //acca.close();

    partita->last(x,y,z);
    if (x<D&&y<D&&z<D)
        cubo[x][y][z] = partita->get(x,y,z);

    Nodo *n_, *n = new Nodo(cubo, &val[0], depth, !m_o);

    //acca.open("creato",std::ofstream::out|std::ofstream::app);
    //acca<<"nodo radice "<<(n->M_o()?'O':'X')<<"\n";
    //acca.close();

    float ev,Max;
    if (m_o) Max = -1000;
        else Max = 1000;
    u a,b,c;

    for (a=0; a<D; a++)
        for (b=0; b<D; b++)
            for (c=0; c<D; c++)
            {
                if (cubo[a][b][c]==Partita::nul)
                {
                    n_ = n->genera(a,b,c);
                    if (n_)
                    {
                        //acca.open("creato",std::ofstream::out|std::ofstream::app);
                        //acca<<"nodo  "<<(n_->M_o()?'O':'X')<<" ttt: "<<ttt<<'\n';
                        //acca.close();
                        ev = n_->Eval();
                        //acca.open("creato",std::ofstream::out|std::ofstream::app);
                        //acca<<"ri-nodo "<<ttt<<" ev="<<ev<<"; pmax="<<Max;

						delete n_;
                        if ((m_o?ev>Max:ev<Max))
						{
							buone.clear();
							Max = ev;
							buone.push_back(my_p(a,b,c));
						}
						if (ev==Max)
                        {
							buone.push_back(my_p(a,b,c));
                        }
                        //acca<<"; max="<<Max<<"\n";
                        //acca.close();
					}
                }
            }

    //acca.open("creato",std::ofstream::out|std::ofstream::app);
    //acca<<"fineval: "<<buone.size()<<"\n";
    //acca.close();

    a = rand()%buone.size();
    std::list<my_p>::iterator it=buone.begin();
    for (it=buone.begin(), b=0; b<a; b++, it++);

    x = it->x;
    y = it->y;
    z = it->z;

    cubo[x][y][z] = (m_o)?Partita::op:Partita::xp;

    delete n;
    //acca.open("creato",std::ofstream::out|std::ofstream::app);
    //acca<<"fine play\n";
    //acca.close();
}

void Tess_Deep::SetPartita(Partita* p)
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

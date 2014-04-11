#include "greedy_m.h"


greedy_m::greedy_m(bool r_o, float weak, Partita* p)
    :Tess_Greedy(r_o, p)
{
    wk = weak;
}

void greedy_m::Play(unsigned& x, unsigned& y, unsigned& z)
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
                    if (Eval()>Max+wk)
                    {
                        buone.clear();
                        Max = Eval();
                        buone.push_back(my_p(a,b,c));
                    }
                    if (Eval()>=Max && Eval()<= Max+wk)
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
    cubo[x][y][z] = (m_o)?Partita::op:Partita::xp;
}

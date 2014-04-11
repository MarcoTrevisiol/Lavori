#include "tess_deep.h"
//#include <fstream>

t_pos::t_pos(u x_, u y_, u z_)
	:x(x_), y(y_), z(z_) {}


Tess_Deep::Tess_Deep(bool r_o, u short d, bool prog, Partita* p)
    :IVPlayer(r_o, p)
{
	m_o = r_o;
	
    val[0] = 0.09;
    val[1] = 0.23;
    val[2] = 0.65;
    val[3] = 10;

    val[4] = -0.09;
    val[5] = -0.3;
    val[6] = -1;
    val[7] = -10;
    
    depth = (d?d:1);
    if (depth>=MP) depth = MP-1;
    
    u a,b,c,l;
    for (l=0; l<=depth; l++)
		for (a=0; a<D; a++)
			for (b=0; b<D; b++)
				for (c=0; c<D; c++)
				{
					conf[l][a][b][c] = Partita::nul;
				}

    SetPartita(p);
    max_depth = MP;
    progressivo = prog;
    if (progressivo)
    {
        max_depth = depth;
        depth = 1;
        yinc = 1;
    }
    //std::ofstream deb("deb");
    //deb<<"Creato "<<(progressivo?"prog":"stan")<<" depth "<<depth<<" max_depth "<<max_depth<<'\n';
    //deb.close();
}

#define Count_Case	{case(Partita::op):(m_o)?mi++:ti++;break;case(Partita::xp):(m_o)?ti++:mi++;break;default:break;}
#define Count_Inc	if(ti==0 && mi>0 && mi<5)count[mi-1]++;if(mi==0 && ti>0 && ti<5)count[ti+3]++;
#define Count_All(A,B) mi = ti = 0;for (z=0; z<D; z++)switch (conf[l]A)Count_Case Count_Inc \
			if (mi==3 && ti==0){for (z=0; z<D&&conf[l]A!=Partita::nul; z++);b3.push_back(t_pos B);} \
			if (mi==0 && ti==3){for (z=0; z<D&&conf[l]A!=Partita::nul; z++);c3.push_back(t_pos B);}
			// A deve essere della forma [x][y][z]; B della forma (x,y,z) con gli stessi x,y,z

void Tess_Deep::Count(u l)
{
    for (unsigned i=0; i<DV; i++)
        count[i] = 0;							//Attenzione:
	b3.clear();									//questi vettori sono modificati da Count = il valore è locale
	c3.clear();									//count, b3, c3
	
    u mi,ti;
    u x,y,z;
    for (x=0; x<D; x++)
        for (y=0; y<D; y++)
        {
			Count_All( [x][y][z], (x,y,z) )
			
			Count_All( [x][z][y], (x,z,y) )
			
			Count_All( [z][x][y], (z,x,y) )
        }
    for (x=0; x<D; x++)
    {
		Count_All( [x][z][z], (x,z,z) )

        Count_All( [x][z][D-z-1], (x,z,D-z-1) )
        
        Count_All( [z][x][z], (z,x,z) )

        Count_All( [z][x][D-z-1], (z,x,D-z-1) )

        Count_All( [z][z][x], (z,z,x) )

        Count_All( [z][D-z-1][x], (z,D-z-1,x) )
    }

    Count_All( [z][z][z], (z,z,z) )

    Count_All( [z][D-z-1][z], (z,D-z-1,z) )

    Count_All( [z][z][D-z-1], (z,z,D-z-1) )

    Count_All( [z][D-z-1][D-z-1], (z,D-z-1,D-z-1) )
}

#undef Count_All
#undef Count_Inc
#undef Count_Case

float Tess_Deep::LEval(u l)
{
	Count(l);
	if (l%2==0 && count[2]>0)
    {
//        std::ofstream deb("deb", std::ofstream::app);
//        deb<<"go vinto\n";
//        deb.close();
		return val[3];
    }
	if (l%2==1 && count[6]>0)
    {
//        std::ofstream deb("deb", std::ofstream::app);
//        deb<<"3 nemiche all\n";
//        deb.close();
		return val[7];
    }
	float ps = 0;
//    std::ofstream deb("deb", std::ofstream::app);
//    deb<<"LEval=\n";
	for (u i=0; i<DV; i++)
    {
//        deb<<count[i]<<' ';
		ps += val[i]*count[i];
    }
//    deb<<": "<<ps<<'\n';
//    deb.close();
	return ps;
}

void Tess_Deep::translate(u l, u x, u y, u z)
{
	if (l==depth)
		return;
	u a,b,c;
	for (a=0; a<D; a++)
		for (b=0; b<D; b++)
			for (c=0; c<D; c++)
			{
				conf[l+1][a][b][c] = conf[l][a][b][c];
			}
	conf[l+1][x][y][z] = (l%2^m_o?Partita::op:Partita::xp);
}

float Tess_Deep::Eval(u l)
{
    //std::ofstream deb("deb", std::ofstream::app);
    //deb<<"Eval "<<l<<" depth: "<<depth<<'\n';
    //deb.close();
    float ev=LEval(l);
    if (depth<=l || ev>=val[3] || ev<=val[7])
        return ev;
    float MinMax = (l%2==0?-100:100);
    u a,b,c;
    for (a=0; a<D; a++)
        for (b=0; b<D; b++)
            for (c=0; c<D; c++)
                if (conf[l][a][b][c]==Partita::nul)
                {
                    translate(l,a,b,c);
                    ev = Eval(l+1);
                    if ((l%2==0?MinMax<ev:MinMax>ev))
                    {
                        MinMax = ev;
                    }
                }
    return MinMax;
}

void Pick_Pos(std::list<t_pos> &lis, u& x, u& y, u& z)
{
	u a,b;
	a = rand()%lis.size();
	std::list<t_pos>::iterator it;
	for (it=lis.begin(), b=0; b<a; b++, it++);
	x = it->x;
	y = it->y;
	z = it->z;
}

void Tess_Deep::Play(u& x, u& y, u& z)
{
    //std::ofstream deb("deb", std::ofstream::app);
    //deb<<"Play "<<(progressivo?"prog":"stan")<<" depth "<<depth<<" max_depth "<<max_depth<<'\n';
    //deb.close();
    partita->last(x,y,z);
	if (x<D&&y<D&&z<D)
		conf[0][x][y][z] = partita->get(x,y,z);
	
	u a,b,c;
	
	if (LEval(0)>=val[3] && b3.size()>0)
	{
		Pick_Pos(b3,x,y,z);
		conf[0][x][y][z] = (m_o)?Partita::op:Partita::xp;
		return;
	}
	
    float ev,Max = -100;
	
	for (a=0; a<D; a++)
		for (b=0; b<D; b++)
			for (c=0; c<D; c++)
				if (conf[0][a][b][c]==Partita::nul)
				{
					translate(0,a,b,c);
                    //if (LEval(1)+0.2>Max)
                    {
                        ev = Eval(1);
                        //std::ofstream deb("deb", std::ofstream::app);
                        //deb<<a<<b<<c<<": L="<<LEval(1)<<" P="<<ev<<'\n';
                        //deb.close();
                        if (Max<ev)
                        {
                            Max = ev;
                            buone.clear();
                            buone.push_back(t_pos(a,b,c));
                        }
                        else if (Max==ev)
                        {
                            buone.push_back(t_pos(a,b,c));
                        }
                    }
				}

	Pick_Pos(buone,x,y,z);
    conf[0][x][y][z] = (m_o)?Partita::op:Partita::xp;
    //mancherebbe il caso in cui non ci sono mosse buone <=> errori+patta
    //std::ofstream deb("deb", std::ofstream::app);
    //deb<<"scelta: "<<x<<y<<z<<" con "<<Max<<"\n\n\n";
    //deb.close();

    if (progressivo && depth<max_depth)
    {
        yinc++;
        if (yinc%2==0)
            depth++;
    }
}

void Tess_Deep::SetPartita(Partita* p)
{
    IVPlayer::SetPartita(p);
    u a,b,c;
    for (a=0; a<D; a++)
		for (b=0; b<D; b++)
			for (c=0; c<D; c++)
			{
				conf[0][a][b][c] = (!p)?Partita::nul:p->get(a,b,c);
			}
    if (progressivo)
        depth = 1;
}

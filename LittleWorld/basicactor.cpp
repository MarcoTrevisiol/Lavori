#include "basicactor.h"

BasicActor::BasicActor(Field* pt)
{
    ptF = pt;
    x = rand()%100;
    y = rand()%100;
}

int BasicActor::getx()
{
    return x;
}

int BasicActor::gety()
{
    return y;
}

unsigned BasicActor::getlp()
{
    return lifepoints;
}

void BasicActor::inflict(int lp)
{
    lifepoints -= lp;
}

void BasicActor::setptF(Field* pt)
{
    ptF = pt;
}

Field* BasicActor::getptF()
{
    return ptF;
}

void BasicActor::Act()
{

}

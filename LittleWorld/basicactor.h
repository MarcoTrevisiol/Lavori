#ifndef BASICACTOR_H
#define BASICACTOR_H

#include "mainhead.h"

class BasicActor
{
public:
    BasicActor(Field* pt = 0);

    int getx();
    int gety();
    unsigned getlp();
    void inflict(int lp);

    void setptF(Field* pt);
    Field* getptF();

    virtual void Act();

protected:
    int x,y;
    unsigned lifepoints;
    Field* ptF;
};

#endif // BASICACTOR_H

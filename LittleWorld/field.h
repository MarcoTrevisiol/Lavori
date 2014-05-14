#ifndef FIELD_H
#define FIELD_H

#include "mainhead.h"

class Field
{
public:
    Field();

    BasicActor* AddActor(typeAct t);

    list<BasicActor>::iterator it;

private:
    list<BasicActor> actors;
};

#endif // FIELD_H

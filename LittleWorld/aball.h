#ifndef ABALL_H
#define ABALL_H

#include "basicactor.h"

class ABall : public BasicActor
{
public:
    ABall(Field* pt = 0);

    virtual void Act();
};

#endif // ABALL_H

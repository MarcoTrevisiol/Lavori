#include "aball.h"

ABall::ABall(Field *pt)
    :BasicActor(pt)
{
}

void ABall::Act()
{
    x += rand()%5-2;
    y += rand()%5-2;
}

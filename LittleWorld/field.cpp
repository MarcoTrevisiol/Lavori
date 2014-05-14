#include "field.h"
#include "basicactor.h"

Field::Field()
{
}


BasicActor* Field::AddActor(typeAct t)
{
    BasicActor* ba;
    switch (t)
    {
        default:
        ba = new BasicActor(this);
        actors.push_back(*ba);
        return &(actors.back());
    }
}

#include "field.h"
#include "basicactor.h"
#include "aball.h"

Field::Field()
{

}


BasicActor* Field::AddActor(typeAct t)
{
    BasicActor* ba;
    switch (t)
    {
    case (aball):
        ba = new ABall(this);
        actors.push_back(*ba);
        return &(actors.back());
    default:
        ba = new BasicActor(this);
        actors.push_back(*ba);
        return &(actors.back());
    }
}

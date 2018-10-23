#include "TrainStationLink.h"
#include "TrainStation.h"

#include <iostream>

using namespace std;
using namespace TrainsSimulation;

TrainStationLink::TrainStationLink(TrainStation* src, TrainStation* dst, int length):
src(src),
dst(dst),
length(length),
status(TrainStationLinkStatus::Vacant)
{
}

TrainStationLink::~TrainStationLink()
{

}

string TrainStationLink::getName()
{
    return this->src->getName() + "->" + this->dst->getName();
}

string TrainStationLink::getCrypticName()
{
    return "s" + to_string(this->src->getIndex()) + "->s" + to_string(this->dst->getIndex());
}

TrainStation* TrainStationLink::getDest()
{
    return this->dst;
}

TrainStation* TrainStationLink::getSrc()
{
    return this->src;
}

int TrainStationLink::getLength()
{
    return this->length;
}

void TrainStationLink::toggleStatus()
{
    switch(status)
    {
        case TrainStationLinkStatus::Vacant:
            status = TrainStationLinkStatus::InUse;
            break;
        case TrainStationLinkStatus::InUse:
            status = TrainStationLinkStatus::Vacant;
            break;
    }
}
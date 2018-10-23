#include "TrainStation.h"
#include "TrainStationLink.h"
#include <iostream>

using namespace TrainsSimulation;
using namespace std;
TrainStation::~TrainStation()
{
}

TrainStation::TrainStation(string name, int index):
name(name),
index(index),
trainStationStatus(TrainStationStatus::Waiting),
lastClosed(-1)
{
}

string TrainStation::getName(void)
{
    return name;
}

int TrainStation::getIndex()
{
    return index;
}

void TrainStation::setPopularity(double pop)
{
    this->popularity = pop;
}

void TrainStation::addOutLink(TrainStationLink* outLink)
{
    this->outLinks.insert(make_pair(outLink->getDest(), outLink));
}

TrainStationLink* TrainStation::getOutLink(TrainStation* dest)
{
    return this->outLinks.find(dest)->second;
}

map<TrainStation*, TrainStationLink*>* TrainStation::getOutLinks()
{
    return &(this->outLinks);
}

double TrainStation::getPopularity()
{
    return this->popularity;
}

vector<int>* TrainStation::getRecordedIntervals()
{
    return &(this->recordedIntervals);
}

void TrainStation::toggleStatus(int ticks)
{
    switch(trainStationStatus)
    {
        case TrainStationStatus::Waiting:
            if (lastClosed != -1)
            {
                recordedIntervals.push_back(ticks - lastClosed);
            }
            trainStationStatus = TrainStationStatus::Loading;
            break;
        case TrainStationStatus::Loading:
            lastClosed = ticks;
            trainStationStatus = TrainStationStatus::Waiting;
            break;
    }
}
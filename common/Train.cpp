#include "Train.h"
#include <iostream>
#include <string>
#include "TrainStation.h"
#include "TrainStationLink.h"
#include <vector>
#include <math.h>

using namespace std;
using namespace TrainsSimulation;

Train::Train(string name, vector<TrainStation*>* trainLine, int position, TrainDirection dir):
name(name),
trainStatus(TrainStatus::WaitingToLoad),
position(position),
trainLine(trainLine),
direction(dir)
{
    setNextLink();
}

Train::~Train()
{

}

void Train::tick(int ticks)
{
    switch(trainStatus)
    {
        case TrainStatus::Loading:
            load(ticks);
            break;
        case TrainStatus::Travelling:
            travel(ticks);
            break;
        case TrainStatus::WaitingToLoad:
            if (getTrainStation()->load(ticks))
            {
                load(ticks);
            }
            else
            {
                idleTicks.push_back(ticks);
            }
            break;
        case TrainStatus::WaitingToTravel:
            if (getTrainStationLink()->grantEntry())
            {
                travel(ticks);
            }
            else
            {
                idleTicks.push_back(ticks);
            }
            break;
    }
}

string Train::getPos(void)
{
    switch(trainStatus)
    {
        case TrainStatus::Travelling:
            return getTrainStationLink()->getCrypticName();
        case TrainStatus::Loading:
        case TrainStatus::WaitingToLoad:
        case TrainStatus::WaitingToTravel:
            return "s" + to_string(getTrainStation()->getIndex());
    }
}

string Train::getReadablePos(void)
{
    switch(trainStatus)
    {
        case TrainStatus::Travelling:
            return getTrainStationLink()->getName();
        case TrainStatus::Loading:
        case TrainStatus::WaitingToLoad:
        case TrainStatus::WaitingToTravel:
            return getTrainStation()->getName();
    }
}

string Train::getName(void)
{
    return this->name;
}

void Train::travel(int ticks)
{
    if (trainStatus == TrainStatus::WaitingToTravel)
    {
        trainStatus = TrainStatus::Travelling;
        counter = trainStationLink->getLength();
        cerr << "[Travel][" + getTrainStationLink()->getName() + "][" + getName() + "][" + to_string(counter) + "][start]\n";
    }

    counter--;

    if (counter == 0)
    {
        getTrainStationLink()->toggleStatus();
        trainStatus = TrainStatus::WaitingToLoad;
        
        // Set current position on trainLine
        goNextStation();
    }
   
    cerr << "[Travel][" + getTrainStationLink()->getName() + "][" + getName() + "][" + to_string(counter) + "][active]\n";
}

void Train::load(int ticks)
{
    if (trainStatus == TrainStatus::WaitingToLoad)
    {
        trainStatus = TrainStatus::Loading;
        // Calculate time needed to load passengers
        counter = ceil(getTrainStation()->getPopularity() * static_cast<double>(rand() % 10 + 1));

        cerr << "[Load][" + getTrainStation()->getName() + "][" + getName() + "][" + to_string(counter) + "][start]\n";
    }

    counter--;
    if (counter == 0)
    {
        trainStatus = TrainStatus::WaitingToTravel;
        getTrainStation()->toggleStatus(ticks);

        // Set next TrainStationLink
        setNextLink();

    }
    cerr << "[Load][" + getTrainStation()->getName() + "][" + getName() + "][" + to_string(counter) + "][active]\n";
}

TrainStationLink* Train::getTrainStationLink(void)
{
    return this->trainStationLink;
}

TrainStation* Train::getTrainStation(void)
{
    return this->trainLine->at(position);
}

void Train::changeDirection()
{
    switch(direction)
    {
        case TrainDirection::North:
            this->direction = TrainDirection::South;
            break;
        case TrainDirection::South:
            this->direction = TrainDirection::North;
            break;
    }
}

vector<int>* Train::getIdleTicks()
{
    return &(this->idleTicks);
}

void Train::goNextStation()
{
    switch(direction)
    {
        case TrainDirection::North:
            position++;
            break;
        case TrainDirection::South:
            position--;
            break;
    }

    // Change direction of train when reach either end of trainLine
    if (position == 0 || position == trainLine->size() - 1)
    {
        changeDirection();
    }
    
}

void Train::setNextLink() {
    switch(direction)
    {
        case TrainDirection::North:
            trainStationLink = getTrainStation()->getOutLink(trainLine->at(position + 1));
            break;
        case TrainDirection::South:
            trainStationLink = getTrainStation()->getOutLink(trainLine->at(position - 1));
            break;
    }
}

void Train::setStatus(TrainStatus status) {
    trainStatus = status;
}

TrainStatus Train::getStatus() {
    return trainStatus;
}
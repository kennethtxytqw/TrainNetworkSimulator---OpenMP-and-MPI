#include "MpiTrainStationLink.h"
#include "Train.h"
#include <mpi.h>
#include <iostream>

using namespace std;
using namespace TrainsSimulation;

MpiTrainStationLink::MpiTrainStationLink(TrainStation* src, TrainStation* dst, int length):
TrainStationLink(src, dst, length)
{

}

Train* MpiTrainStationLink::getNextTrain() {
    Train* train = trains.at(0);
    return train;
}

Train* MpiTrainStationLink::pop() {
    Train* train = trains.at(0);
    trains.erase(trains.begin());
    return train;
}

bool MpiTrainStationLink::hasTrain() {
    return trains.size() > 0;
}

void MpiTrainStationLink::queueTrain(Train* train) {
    trains.push_back(train);
}
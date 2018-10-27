#include "MpiTrainStation.h"
#include "Train.h"
#include <iostream>

using namespace std;
using namespace TrainsSimulation;

MpiTrainStation::MpiTrainStation(string name, int index):
TrainStation(name, index) {
    ticksLeftToLoad = 0;
}

void MpiTrainStation::tick() {
    ticksLeftToLoad--;
}

void MpiTrainStation::queueTrain(Train* train, int tick) {
    if (queuedTrains.size() == 0) {
        toggleStatus(tick);
        ticksLeftToLoad = getPopularity() * static_cast<double>(rand() % 10 + 1) + 0.9;
    }
    queuedTrains.push_back(train);
}

bool MpiTrainStation::hasReadyTrain() {
    if (ticksLeftToLoad == 0 && queuedTrains.size() > 0) {
        return true;
    }
    return false;
}

Train* MpiTrainStation::getReadyTrain(int tick) {
    Train* train = queuedTrains.at(0);
    queuedTrains.erase(queuedTrains.begin());
    if (queuedTrains.size() > 0) {
        ticksLeftToLoad = getPopularity() * static_cast<double>(rand() % 10 + 1) + 0.9;
    } else {
        toggleStatus(tick);
    }
    cerr << "stn[" + getName() + "] popped " + train->getName() + "\n";
    return train;
}
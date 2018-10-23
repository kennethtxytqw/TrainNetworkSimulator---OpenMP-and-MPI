#include "MpiTrainStation.h"

using namespace TrainsSimulation;

MpiTrainStation::MpiTrainStation(string name, int index):
TrainStation(name, index) {
    ticksLeftToLoad = 0;
}

void MpiTrainStation::tick() {
    if (ticksLeftToLoad == 0 && queuedTrains.size() > 0) {
        ticksLeftToLoad = getPopularity() * static_cast<double>(rand() % 10 + 1);
    } else if (ticksLeftToLoad > 0) {
        ticksLeftToLoad--;
    }
}

void MpiTrainStation::queueTrain(Train* train) {
    queuedTrains.push_back(train);
}

bool MpiTrainStation::hasReadyTrain() {
    if (ticksLeftToLoad == 0 && queuedTrains.size() > 0) {
        return true;
    }
    return false;
}

Train* MpiTrainStation::getReadyTrain() {
    Train* train = queuedTrains.at(0);
    queuedTrains.erase(queuedTrains.begin());
    if (queuedTrains.size() > 0) {
        ticksLeftToLoad = getPopularity() * static_cast<double>(rand() % 10 + 1);
    }
    return train;
}
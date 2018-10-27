#pragma once
#include <string>
#include "TrainStation.h"

using namespace std;
namespace TrainsSimulation
{
    class Train;
    class MpiTrainStation: virtual public TrainStation
    {
        public:
            MpiTrainStation(string name, int index);
            ~MpiTrainStation();
            void tick();
            void queueTrain(Train* train, int tick);
            bool hasReadyTrain();
            Train* getReadyTrain(int tick);
        private:
            vector<Train*> queuedTrains;
            int ticksLeftToLoad;
    };
}
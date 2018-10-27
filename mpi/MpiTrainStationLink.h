#pragma once
#include "TrainStationLink.h"
#include <vector>

namespace TrainsSimulation
{
    
    class TrainStation;
    class Train;
    class MpiTrainStationLink: virtual public TrainStationLink
    {
        public:
            MpiTrainStationLink(TrainStation* src, TrainStation* dst, int length);
            Train* getNextTrain();
            bool hasTrain();
            Train* pop();
            void queueTrain(Train* train);
        protected:
            vector<Train*> trains;
    };
}
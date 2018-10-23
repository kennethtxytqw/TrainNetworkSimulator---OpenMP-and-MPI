#include "TrainStationLink.h"

namespace TrainsSimulation
{
    class MpiTrainStationLink: virtual TrainStationLink
    {
        public:
            void queueTrain(Train* train);
            void tick();
            
    };
}
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
            void queueTrain(Train* train);
            bool hasReadyTrain();
            Train* getReadyTrain();
        private:
            vector<Train*> queuedTrains;
            int ticksLeftToLoad;
    };
}
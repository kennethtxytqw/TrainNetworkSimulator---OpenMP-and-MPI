#include "TrainsSimulator.h"
#include <map>

using namespace std;

namespace TrainsSimulation
{
    class TrainStation;
    class TrainStationLink;
    class MpiTrainsSimulator: virtual public TrainsSimulator
    {
        public:
            MpiTrainsSimulator();
            void execute();
            void addStation(string station, int index);
    };
}
#pragma once
#include "TrainsSimulator.h"
#include <map>

using namespace std;

namespace TrainsSimulation
{
    class TrainStation;
    class TrainStationLink;
    class OmpTrainsSimulator: virtual public TrainsSimulator
    {
        public:
            OmpTrainsSimulator();
            void execute();
            void addStation(string station, int index) override;
            virtual void addLink(map<TrainStation*, TrainStationLink*> &row, TrainStation* src, int dstIndex, int length) override;
    };
}
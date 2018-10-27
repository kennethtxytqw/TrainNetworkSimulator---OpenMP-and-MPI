#pragma once
#include "TrainsSimulator.h"
#include <map>
#include <iostream>

using namespace std;

namespace TrainsSimulation
{
    class Train;
    class TrainStation;
    class TrainStationLink;
    class MpiTrainStationLink;
    class MpiTrainsSimulator: virtual public TrainsSimulator
    {
        public:
            MpiTrainsSimulator();
            void execute();
            void addStation(string station, int index);
            void addLink(map<TrainStation*, TrainStationLink*> &row, TrainStation* src, int dstIndex, int length);
            Train* getTrain(string name);
        private:
            void introduceNewTrains(int tick);
            void printAllTrainsPos(void);
            void printReadableAllTrainsPos(ostream &stream);
            map<string, Train*> trainNames;
            void distributeLinkLength();
            void sendNextTrain(int stationLinkIndex, int tick);
            int recvStatusOfRunningTrain(int stationLinkIndex, int tick);
    };
}
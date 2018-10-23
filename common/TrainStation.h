#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;
namespace TrainsSimulation
{
    enum class TrainStationStatus
    {
        Loading,
        Waiting
    };
    class Train;
    class TrainStation;
    class TrainStationLink;
    class TrainStation
    {
        public:
            TrainStation(string name, int index);
            ~TrainStation();
            TrainStation* getNext();
            void setNorth(TrainStation &station);
            void setPopularity(double popularity);
            double getPopularity();
            string getName(void);
            int getIndex();
            void addOutLink(TrainStationLink* outLink);
            TrainStationLink* getOutLink(TrainStation* dst);
            map<TrainStation*, TrainStationLink*>* getOutLinks();
            virtual bool load(int ticks){};
            TrainStationStatus getStatus(){return this->trainStationStatus;};
            virtual void toggleStatus(int ticks);
            vector<int>* getRecordedIntervals();
        private:
            string name;
            int index;
            double popularity;
            map<TrainStation*, TrainStationLink*> outLinks;
            TrainStationStatus trainStationStatus;
            vector<int> recordedIntervals;
            int lastClosed;
    };
}
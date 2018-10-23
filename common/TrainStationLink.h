#pragma once
#include <string>

using namespace std;
namespace TrainsSimulation
{
    enum class TrainStationLinkStatus
    {
        InUse,
        Vacant
    };
    class Train;
    class TrainStation;
    class TrainStationLink
    {
        public:
            TrainStationLink(TrainStation* src, TrainStation* dst, int length);
            ~TrainStationLink();
            TrainStation* getSrc();
            TrainStation* getDest();
            string getName();
            string getCrypticName();
            int getLength();
            TrainStationLink* getNextTrainStationLink();  
            virtual bool grantEntry() {return true;};
            TrainStationLinkStatus getStatus() {return this->status;};
            virtual void toggleStatus();
        private:
            TrainStation* src;
            TrainStation* dst;
            int length;
            TrainStationLinkStatus status;
    };
}
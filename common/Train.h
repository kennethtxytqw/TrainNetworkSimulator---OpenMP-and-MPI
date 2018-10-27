#pragma once
#include <string>
#include <vector>

using namespace std;
namespace TrainsSimulation
{
    enum class TrainStatus
    {
        Travelling,
        Loading,
        WaitingToLoad,
        WaitingToTravel
    };
    enum class TrainDirection
    {
        North,
        South
    };
    class TrainStationLink;
    class TrainStation;
    class Train
    {
        public:
            Train(string name, vector<TrainStation*>* trainLinePtr, int position, TrainDirection dir);
            ~Train();
            void tick(int ticks);
            string getName();
            TrainStation* getTrainStation();
            TrainStationLink* getTrainStationLink();
            string getPos();
            string getReadablePos();
            vector<int>* getIdleTicks();
            vector<TrainStation*>* getTrainLine();
            void goNextStation();
            void setNextLink();
            void setStatus(TrainStatus status);
            TrainStatus getStatus();
        private:
            string name;
            TrainStatus trainStatus;
            void travel(int ticks);
            void load(int ticks);
            TrainStationLink* trainStationLink;
            int position;
            int counter;
            void changeDirection();
            TrainDirection direction;
            vector<TrainStation*>* trainLine;
            vector<int> idleTicks;
    };
}
#pragma once

#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

namespace TrainsSimulation
{
    class Train;
    class TrainStation;
    class TrainStationLink;
    class TrainsSimulator
    {
        public:
            TrainsSimulator();
            ~TrainsSimulator(void);
            void execute(void);
            vector<Train*>* getAllTrains(void);
            void printAllTrainsPos(void);
            void printReadableAllTrainsPos(ostream &stream);
            int getThreads(void);
            int getNumTicks();
            map<string, vector<TrainStation*>*>* getTrainLines();
            map<string, int>* getMaxTrains();
            map<string, vector<Train*>*>* getRunningTrainsByLines();
            vector<Train*>* getRunningTrains();
            map<int, TrainStation*>* getStationIndexes();
            map<string, TrainStation*>* getStationNames();
            virtual void addStation(string station, int index);
            void initialize(ifstream &infile);
            virtual void addLink(map<TrainStation*, TrainStationLink*> &row, TrainStation* src, int dstIndex, int length);
            void printAvgWaitingTimes();
        private:
            map<int, TrainStation*> g_stationIndexes;
            map<string, TrainStation*> g_stationNames;
            vector<double> g_popularities;
            map<string, vector<TrainStation*>*> g_trainLines;
            map<string, int> maxTrains;
            map<string, vector<Train*>*> runningTrainsByLines;
            vector<Train*> runningTrains;
            
            int threads;
            int numStations;
            int numTicks;
            void populateStationNames(string line);
            void getLinksForStation(int index, string line);
            void getTrainLine(string line, string trainLineColor);
            void getPopularities(string line);
            void setPopularity(int stnIndex, double pop);
            void addStationToLine(vector<TrainStation*>* trainLine, string station);
            void printTrainLine(vector<TrainStation*>* trainLine);
            void printTrainLinks();
    };
}
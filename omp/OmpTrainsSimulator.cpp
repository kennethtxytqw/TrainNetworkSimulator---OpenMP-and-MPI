#include "OmpTrainsSimulator.h"
#include "OmpTrainStation.h"
#include "OmpTrainStationLink.h"
#include "Train.h"
#include "TrainStation.h"
#include "TrainStationLink.h"
#include <omp.h>
#include <iterator>
#include <iostream>
#include <map>
#include <chrono>

using namespace std;
using namespace TrainsSimulation;

OmpTrainsSimulator::OmpTrainsSimulator():
TrainsSimulator()
{

}

void OmpTrainsSimulator::execute(void)
{
    omp_set_num_threads(getThreads());
    cerr 
    << "Starting openmp train simulation with " 
    << omp_get_num_threads()
    << " threads." << endl;


    for(int ticks = 0; ticks < getNumTicks(); ticks++)
    {
        int i, j;
        map<string, vector<TrainStation*>*>::iterator lineBeginItr = getTrainLines()->begin();

        // Introduce new trains if needed
        #pragma omp parallel for
        for(int i = 0; i < getTrainLines()->size(); i++)
        {
            map<string, vector<TrainStation*>*>::iterator lineItr = std::next(lineBeginItr, i);
            string lineColor = lineItr->first;
            vector<Train*>* runningTrainsPerLinePtr = getRunningTrainsByLines()->find(lineColor)->second;
            int maxTrainsPerLine = getMaxTrains()->find(lineColor)->second;

            // If not yet at full capacity insert train at head of the line
            if (runningTrainsPerLinePtr->size() < maxTrainsPerLine)
            {
                vector<TrainStation*>* trainLinePtr = lineItr->second;
                Train* trainPtr = new Train(lineColor + to_string(runningTrainsPerLinePtr->size()),
                                            trainLinePtr,
                                            0,
                                            TrainDirection::North);
                runningTrainsPerLinePtr->push_back(trainPtr);
                
                #pragma omp critical(addingTrain)
                getRunningTrains()->push_back(trainPtr);
                cerr << "Introduced train into " + lineColor + " line. Current size: " + to_string(runningTrainsPerLinePtr->size()) + "\n";
            }

            // If not yet at full capacity insert train at tail of the line
            if (runningTrainsPerLinePtr->size() < maxTrainsPerLine)
            {
                vector<TrainStation*>* trainLinePtr = lineItr->second;
                Train* trainPtr = new Train(lineColor + to_string(runningTrainsPerLinePtr->size()),
                                            trainLinePtr,
                                            trainLinePtr->size() - 1,
                                            TrainDirection::South);
                runningTrainsPerLinePtr->push_back(trainPtr);
                
                #pragma omp critical(addingTrain)
                getRunningTrains()->push_back(trainPtr);
                cerr << "Introduced train into " + lineColor + " line. Current size: " + to_string(runningTrainsPerLinePtr->size()) + "\n";
            }           
        }
        cerr << "######\nTick " + to_string(ticks) + "\n######\n";
        vector<Train*>::iterator trainBeginItr = getRunningTrains()->begin();
        #pragma omp parallel
        {
            int threadId = omp_get_thread_num();
            if (threadId < getRunningTrains()->size())
            {
                // As long as the trains do not change position in this vector, the same thread will operate the same train every time
                Train* trainPtr = getRunningTrains()->at(threadId);
                trainPtr->tick(ticks);
            }
        }

        cout << ticks << ": ";
        printAllTrainsPos();
        printReadableAllTrainsPos(cerr);
    }
}

void OmpTrainsSimulator::addStation(string station, int index) 
{
    OmpTrainStation* trainStation = new OmpTrainStation(station, index);
    getStationNames()->insert(make_pair(station, trainStation));
    getStationIndexes()->insert(make_pair(index, trainStation));
    cerr << trainStation->getName() << "-" << index << endl;
}


void OmpTrainsSimulator::addLink(map<TrainStation*, TrainStationLink*> &row, TrainStation* src, int dstIndex, int length)
{
    if (length > 0) 
    {
        TrainStation* dst = getStationIndexes()->find(dstIndex)->second;
        TrainStationLink* link = new OmpTrainStationLink(src, dst, length);
        src->addOutLink(link);
        getStationLinks()->push_back(link);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputfile>" << endl; 
        return EXIT_FAILURE;
    }
    
    ifstream infile(argv[1]);
    OmpTrainsSimulator ts = OmpTrainsSimulator();
    ts.initialize(infile);

    auto wcts = std::chrono::system_clock::now();
    ts.execute();
    std::chrono::duration<double> wctduration = (std::chrono::system_clock::now() - wcts);

    ts.printAvgWaitingTimes();

    cout << "Time elapsed for running of train network " << wctduration.count() << "seconds.\n";

    ts.printAllTrainsIdleTicks(cerr);
    return 0;
}

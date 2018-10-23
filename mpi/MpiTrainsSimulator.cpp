#include <iostream>
#include <chrono>
#include "mpi.h"

#include "MpiTrainStation.h"
#include "MpiTrainsSimulator.h"

using namespace TrainsSimulation;

MpiTrainsSimulator::MpiTrainsSimulator():
TrainsSimulator()
{

}

void MpiTrainsSimulator::introduceNewTrains() {
    map<string, vector<TrainStation*>*>::iterator lineBeginItr = getTrainLines()->begin();

        // Introduce new trains if needed
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
                getRunningTrains()->push_back(trainPtr);
                cerr << "Introduced train into " + lineColor + " line. Current size: " + to_string(runningTrainsPerLinePtr->size()) + "\n";
            }           
        }
}

void MpiTrainsSimulator::execute(void) {
    
    for(int tick = 0; tick < getNumTicks(); tick++)
    {
        introduceNewTrains();
        
        for(int stationLinkIndex = 0; stationLinkIndex < getStationLinks()->size(); stationLinkIndex++)
        {
            // Send the links their trains

            // Receive trains from the links
        }
        
    }
    
}

void MpiTrainsSimulator::addStation(string station, int index) 
{
    MpiTrainStation* trainStation = new MpiTrainStation(station, index);
    getStationNames()->insert(make_pair(station, trainStation));
    getStationIndexes()->insert(make_pair(index, trainStation));
    cerr << trainStation->getName() << "-" << index << endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: mpirun -np <np>" << argv[0] << " <inputfile>" << endl; 
        return EXIT_FAILURE;
    }
    
    ifstream infile(argv[1]);
    MpiTrainsSimulator ts = MpiTrainsSimulator();
    ts.initialize(infile);

    MPI_Init(NULL, NULL);
    int world_size;
    int world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    if (world_size < ts.getStationLinks()->size() + 1) {
        cerr << "Usage: mpirun -np " + to_string(ts.getStationLinks()->size() + 1) +  argv[0] + " <inputfile>\n";
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == ts.getStationLinks()->size()) {
        auto wcts = std::chrono::system_clock::now();
        ts.execute();
        std::chrono::duration<double> wctduration = (std::chrono::system_clock::now() - wcts);

        ts.printAvgWaitingTimes();

        cout << "Time elapsed for running of train network " << wctduration.count() << "seconds.\n";

        ts.printAllTrainsIdleTicks(cerr);
    } else {
        TrainStationLink* tsl = ts.getStationLinks()->at(world_rank);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}

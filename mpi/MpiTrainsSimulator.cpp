#include <iostream>
#include <chrono>
#include <mpi.h>
#include <algorithm>

#include "MpiTrainStation.h"
#include "MpiTrainsSimulator.h"
#include "MpiTrainStationLink.h"
#include "Train.h"
#include "TrainStation.h"
#include "TrainStationLink.h"

using namespace std;
using namespace TrainsSimulation;

void simulateStationLink(int world_rank, int world_size);

MpiTrainsSimulator::MpiTrainsSimulator():
TrainsSimulator()
{

}

void MpiTrainsSimulator::introduceNewTrains(int tick) {
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
                trainNames.insert(pair<string, Train*>(trainPtr->getName(), trainPtr));

                dynamic_cast<MpiTrainStation*>(*(trainLinePtr->begin()))->queueTrain(trainPtr, tick);
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
                trainNames.insert(pair<string, Train*>(trainPtr->getName(), trainPtr));
                dynamic_cast<MpiTrainStation*>(*(trainLinePtr->end()-1))->queueTrain(trainPtr, tick);
                cerr << "Introduced train into " + lineColor + " line. Current size: " + to_string(runningTrainsPerLinePtr->size()) + "\n";
            }           
        }
}

void MpiTrainsSimulator::execute(void) {
    
    for(int tick = 0; tick < getNumTicks(); tick++)
    {
        cerr << "####\n" + to_string(tick) + " tick\n####\n";
        introduceNewTrains(tick);
        
        cout << to_string(tick) + ": ";

        string trainName;
        MPI_Status status;
        Train* trainPtr;
        int rcvSize;
        char rcvBuf[3];
        for (int i = 0; i < getStationIndexes()->size(); i++) 
        {
            MpiTrainStation* stnPtr = dynamic_cast<MpiTrainStation*>((getStationIndexes()->find(i))->second);
            stnPtr->tick();
            if (stnPtr->hasReadyTrain()) {
                trainPtr = stnPtr->getReadyTrain(tick);
                // send train to its next link
                trainPtr->setStatus(TrainStatus::WaitingToTravel);
                
                MpiTrainStationLink* mpiStnLink = dynamic_cast<MpiTrainStationLink*>(trainPtr->getTrainStationLink());
                mpiStnLink->queueTrain(trainPtr);
            }
        }

        for (int stationLinkIndex = 0; stationLinkIndex < getStationLinks()->size(); stationLinkIndex++)
        {
            int ticksLeftOnStationLink = recvStatusOfRunningTrain(stationLinkIndex, tick);
            if (ticksLeftOnStationLink <= 0) {
                sendNextTrain(stationLinkIndex, tick);
            } else {
                // Idle as there is a train using the station link
            }
        }
        printAllTrainsPos();
        printReadableAllTrainsPos(cerr);
    }
    
}

int MpiTrainsSimulator::recvStatusOfRunningTrain(int stationLinkIndex, int tick) {
    MPI_Status status;
    int ticksLeftOnStationLink;
    Train* trainPtr;
    
    // cerr << "[Root] receiving [" + to_string(stationLinkIndex) + "]\n";
    MPI_Recv(&ticksLeftOnStationLink, 1, MPI_INT, stationLinkIndex, tick, MPI_COMM_WORLD, &status);
    if (ticksLeftOnStationLink == 0) {
        MpiTrainStationLink* link = dynamic_cast<MpiTrainStationLink*>(getStationLinks()->at(stationLinkIndex));
        // Train has exited link
        trainPtr = link->pop();
        trainPtr->goNextStation();
        trainPtr->setNextLink();
        trainPtr->setStatus(TrainStatus::WaitingToLoad);
        dynamic_cast<MpiTrainStation*>(trainPtr->getTrainStation())->queueTrain(trainPtr, tick);
    }
    return ticksLeftOnStationLink;

}

void MpiTrainsSimulator::sendNextTrain(int stationLinkIndex, int tick) {
    
    MpiTrainStationLink* trainStationLink = dynamic_cast<MpiTrainStationLink*>(getStationLinks()->at(stationLinkIndex));
    int ticksToMake;
    if (trainStationLink->hasTrain()) {
        
        Train* train = trainStationLink->getNextTrain();
        train->setStatus(TrainStatus::Travelling);
        ticksToMake = trainStationLink->getLength();
    } else {
        ticksToMake = 0;
    }
    
    // cerr << "[Root] sending [" + to_string(stationLinkIndex) + "]: " + to_string(ticksToMake) + "\n";
    MPI_Send(&ticksToMake, 1, MPI_INT, stationLinkIndex, tick, MPI_COMM_WORLD);
}

void MpiTrainsSimulator::printAllTrainsPos(void)
{    
    for (int i = 0; i < getRunningTrains()->size(); i++)
    {
        Train* trainPtr = getRunningTrains()->at(i);
        cout << trainPtr->getName() + "-" + trainPtr->getPos() + ", ";
    }
    cout << endl;
}

void MpiTrainsSimulator::printReadableAllTrainsPos(ostream &stream)
{    
    for (int i = 0; i < getRunningTrains()->size(); i++)
    {
        Train* trainPtr = getRunningTrains()->at(i);
        stream << trainPtr->getName() + "-" + trainPtr->getReadablePos() + ", ";
    }
    stream << endl;
}

void MpiTrainsSimulator::addStation(string station, int index) 
{
    MpiTrainStation* trainStation = new MpiTrainStation(station, index);
    getStationNames()->insert(make_pair(station, trainStation));
    getStationIndexes()->insert(make_pair(index, trainStation));
    // cerr << trainStation->getName() << "-" << index << endl;
}

void MpiTrainsSimulator::addLink(map<TrainStation*, TrainStationLink*> &row, TrainStation* src, int dstIndex, int length)
{
    if (length > 0) 
    {
        TrainStation* dst = getStationIndexes()->find(dstIndex)->second;
        MpiTrainStationLink* link = new MpiTrainStationLink(src, dst, length);
        src->addOutLink(link);
        getStationLinks()->push_back(link);
    }
}

Train* MpiTrainsSimulator::getTrain(string name) {
    return trainNames.find(name)->second;
}

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int world_size;
    int world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (argc < 2) {
        cerr << "Usage: mpirun -np <np>" << argv[0] << " <inputfile>" << endl; 
        return EXIT_FAILURE;
    }


    if (world_rank == world_size-1) {
        // Simlulates a train network master that knows everything
        ifstream infile(argv[1]);
        MpiTrainsSimulator ts = MpiTrainsSimulator();
        ts.initialize(infile);

        if (world_size < ts.getStationLinks()->size() + 1) {
            cerr << "Usage: mpirun -np " + to_string(ts.getStationLinks()->size() + 1) +  argv[0] + " <inputfile>\n";
            MPI_Finalize();
            return EXIT_FAILURE;
        }

        auto wcts = std::chrono::system_clock::now();
        
        int ticksToBeMade = ts.getNumTicks();
        MPI_Bcast(&ticksToBeMade, 1, MPI_INT, world_rank, MPI_COMM_WORLD);
        ts.execute();
        std::chrono::duration<double> wctduration = (std::chrono::system_clock::now() - wcts);

        ts.printAvgWaitingTimes();

        cout << "Time elapsed for running of train network " << wctduration.count() << "seconds.\n";

        ts.printAllTrainsIdleTicks(cerr);
    } else {
        simulateStationLink(world_rank, world_size);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}

void simulateStationLink(int world_rank, int world_size) {
    MPI_Status status;
    int ticksLeftOnTransit = -1;
    int ticksToBeMade;
    
    MPI_Bcast(&ticksToBeMade, 1, MPI_INT, world_size-1, MPI_COMM_WORLD);
    
    for(int tick = 0; tick < ticksToBeMade; tick++)
    {
        // Send out status of running train
        
        MPI_Ssend(&ticksLeftOnTransit, 1, MPI_INT, world_size-1, tick, MPI_COMM_WORLD);
        
        // cerr << "[" + to_string(world_rank) + "] sent ticksLeftOnTransit:" + to_string(ticksLeftOnTransit) + "\n";

        if (ticksLeftOnTransit <= 0) {
            // Receive new train
            MPI_Recv(&ticksLeftOnTransit, 1, MPI_INT, world_size-1, tick, MPI_COMM_WORLD, &status);
            // cerr << "[" + to_string(world_rank) + "] received ticksLeftOnTransit:" + to_string(ticksLeftOnTransit) +  "\n";
        }

        ticksLeftOnTransit--;
    }
}
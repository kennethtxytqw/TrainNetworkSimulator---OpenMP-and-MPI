#include "TrainsSimulator.h"
#include "TrainStation.h"
#include "TrainStationLink.h"
#include "Train.h"
#include <algorithm>
#include <numeric>

using namespace TrainsSimulation;
using namespace std;

string g_comma = ",";
string g_space = " ";


TrainsSimulator::TrainsSimulator()
{
}

TrainsSimulator::~TrainsSimulator(void)
{

}

void TrainsSimulator::initialize(ifstream &fp)
{
    string line;
    // Get number of stations
    getline(fp, line);
    numStations = stoi(line);
    cerr << "Number of stations: " << numStations << endl;

    // Get station names and assign them indexes
    getline(fp, line);
    populateStationNames(line);

    // Populate adjacency matrix
    for(int i = 0; i < numStations; i++) 
    {
        getline(fp, line);
        getLinksForStation(i, line);      
    }
    printTrainLinks();

    // Get popularities
    getline(fp, line);
    getPopularities(line);

    // Get the lines
    // Get green line
    getline(fp, line);
    getTrainLine(line, "g");

    // // Get yellow line
    getline(fp, line);
    getTrainLine(line, "y");

    // // Get blue line
    getline(fp, line);
    getTrainLine(line, "b");   

    // Get number of ticks in simulation
    getline(fp, line);
    numTicks = stoi(line);

    // // Get number of trains per line
    getline(fp, line);
    int maxTrainPerLine = stoi(line);
    maxTrains.insert(make_pair("g", maxTrainPerLine));
    threads += maxTrainPerLine;
    getline(fp, line);
    maxTrainPerLine = stoi(line);
    maxTrains.insert(make_pair("y", maxTrainPerLine));
    threads += maxTrainPerLine;
    getline(fp, line);
    maxTrainPerLine = stoi(line);
    maxTrains.insert(make_pair("b", maxTrainPerLine));
    threads += maxTrainPerLine;
    cerr 
    << "G: " << maxTrains.find("g")->second << endl 
    << "Y: " << maxTrains.find("y")->second << endl
    << "B: " << maxTrains.find("b")->second << endl; 
}

void TrainsSimulator::populateStationNames(string line)
{
    int pos = 0;
    string token;
    int count = 0;
    while ((pos = line.find(g_comma)) != string::npos) 
    {
        token = line.substr(0, pos);
        addStation(token, count);
        line.erase(0, pos + g_comma.length());
        count++;
    }
    token = line.substr(0, line.size()-1);
    addStation(token, count);
}

void TrainsSimulator::addStation(string station, int index) 
{
    TrainStation* trainStation = new TrainStation(station, index);
    g_stationNames.insert(make_pair(station, trainStation));
    g_stationIndexes.insert(make_pair(index, trainStation));
    cerr << trainStation->getName() << "-" << index << endl;
}

void TrainsSimulator::getLinksForStation(int index, string line)
{
    int pos = 0;
    string token;
    map<TrainStation*, TrainStationLink*> outwardLinks;
    int dist;
    TrainStation* src = g_stationIndexes.find(index)->second;
    int dstIndex = 0;
    while ((pos = line.find(g_space)) != string::npos) 
    {
        token = line.substr(0, pos);
        dist = stoi(token);
        addLink(outwardLinks, src, dstIndex, dist);
        line.erase(0, pos + g_space.length());
        dstIndex++;
    }
    token = line.substr(0, line.size()-1);
    dist = stoi(token);
    addLink(outwardLinks, src, dstIndex, dist);
}

void TrainsSimulator::addLink(map<TrainStation*, TrainStationLink*> &row, TrainStation* src, int dstIndex, int length)
{
    if (length > 0) 
    {
        TrainStation* dst = g_stationIndexes.find(dstIndex)->second;
        TrainStationLink* link = new TrainStationLink(src, dst, length);
        src->addOutLink(link);
    }
}

void TrainsSimulator::getPopularities(string line)
{   
    int pos = 0;
    string token;
    double pop;
    int index = 0;
    while ((pos = line.find(g_comma)) != string::npos) 
    {
        token = line.substr(0, pos);
        pop = stod(token);
        setPopularity(index, pop);
        line.erase(0, pos + g_comma.length());
        index++;
    }
    token = line.substr(0, line.size()-1);
    pop = stod(token);
    setPopularity(index, pop);
}

void TrainsSimulator::setPopularity(int stnIndex, double pop)
{
    TrainStation* stnPtr = g_stationIndexes.find(stnIndex)->second;
    stnPtr->setPopularity(pop);
}

void TrainsSimulator::getTrainLine(string line, string trainLineColor)
{
    int pos = 0;
    string token;
    int stationIndex;
    vector<TrainStation*>* trainLine = new vector<TrainStation*>();

    while ((pos = line.find(g_comma)) != string::npos) 
    {
        // For visual purpose - start
        token = line.substr(0, pos);
        addStationToLine(trainLine, token);
        line.erase(0, pos + g_comma.length());
        // For visual purpose - end
    }
    token = line.substr(0, line.size()-1);
    addStationToLine(trainLine, token);
    g_trainLines.insert(make_pair(trainLineColor, trainLine));
    runningTrainsByLines.insert(make_pair(trainLineColor, new vector<Train*>()));
    printTrainLine(g_trainLines.find(trainLineColor)->second);
}

void TrainsSimulator::printTrainLine(vector<TrainStation*>* vecPtr)
{
    vector<TrainStation*>::iterator listItr;
    cerr << "The stations are:" << endl;
    for (listItr = vecPtr->begin();
        listItr != vecPtr->end();
        listItr++)
        {
            TrainStation* stationPtr = *listItr;

            cerr << stationPtr->getName() << " ";

        }
        cerr << endl;
}

void TrainsSimulator::printTrainLinks()
{
    for (int i = 0; i < g_stationIndexes.size(); i++)
    {
        TrainStation* station  = g_stationIndexes.find(i)->second;
        map<TrainStation*, TrainStationLink*>* outLinks = station->getOutLinks();

        for (map<TrainStation*, TrainStationLink*>::iterator iter = outLinks->begin();
        iter != outLinks->end();
        iter++)
        {
            cerr << (iter->second)->getName() << endl;
        }
    }
}

void TrainsSimulator::addStationToLine(vector<TrainStation*>* trainLinePtr, string station) 
{
    map<string, TrainStation*>::iterator iter;
    iter = g_stationNames.find(station);
    if (iter != g_stationNames.end()) 
    {
        trainLinePtr->push_back(iter->second);
    } else
    {
        cerr << "Can't find index of " << station << endl;
    }
}

vector<Train*>* TrainsSimulator::getAllTrains(void)
{
    return &runningTrains;
}

void TrainsSimulator::printAllTrainsPos(void)
{    
    for (int i = 0; i < runningTrains.size(); i++)
    {
        Train* trainPtr = runningTrains.at(i);
        cout << trainPtr->getName() << "-" << trainPtr->getPos() << ", ";
    }
    cout << endl;
}

void TrainsSimulator::printReadableAllTrainsPos(ostream &stream)
{    
    for (int i = 0; i < runningTrains.size(); i++)
    {
        Train* trainPtr = runningTrains.at(i);
        stream << trainPtr->getName() << "-" << trainPtr->getReadablePos() << ", ";
    }
    stream << endl;
}

int TrainsSimulator::getThreads(){
    return this->threads;
}

int TrainsSimulator::getNumTicks()
{
    return this->numTicks;
}

map<string, vector<TrainStation*>*>* TrainsSimulator::getTrainLines()
{
    return &(this->g_trainLines);
}

map<string, int>* TrainsSimulator::getMaxTrains()
{
    return &(this->maxTrains);
}

map<string, vector<Train*>*>* TrainsSimulator::getRunningTrainsByLines()
{
    return &(this->runningTrainsByLines);
}

vector<Train*>* TrainsSimulator::getRunningTrains()
{
    return &(this->runningTrains);
}

map<int, TrainStation*>* TrainsSimulator::getStationIndexes()
{
    return &(this->g_stationIndexes);
}
map<string, TrainStation*>* TrainsSimulator::getStationNames()
{
    return &(this->g_stationNames);
}

void TrainsSimulator::printAvgWaitingTimes()
{
    cout << "Average waiting times:\n";
    for (map<string, vector<TrainStation*>*>::iterator trainLineItr = getTrainLines()->begin();
    trainLineItr != getTrainLines()->end();
    trainLineItr++)
    {
        double totalWaitingTime = 0.0;
        double totalLongestWaitingTime = 0.0;
        double totalShortestWaitingTime = 0.0;

        double intervalsRecorded = 0.0;

        string trainLineColor = trainLineItr->first;
        vector<TrainStation*>* trainLinePtr = trainLineItr->second;

        for (vector<TrainStation*>::iterator trainStnItr = trainLinePtr->begin();
        trainStnItr != trainLinePtr->end();
        trainStnItr++)
        {
            
            TrainStation* trainStnPtr = *trainStnItr;
            vector<int>* recordedIntervalsPtr = trainStnPtr->getRecordedIntervals();

            if (recordedIntervalsPtr->size() > 0) 
            {
                totalWaitingTime += static_cast<double>(accumulate(recordedIntervalsPtr->begin(), recordedIntervalsPtr->end(), 0));
                totalLongestWaitingTime += static_cast<double>(*max_element(recordedIntervalsPtr->begin(), recordedIntervalsPtr->end()));
                totalShortestWaitingTime += static_cast<double>(*min_element(recordedIntervalsPtr->begin(), recordedIntervalsPtr->end()));
            }
            intervalsRecorded += static_cast<double>(recordedIntervalsPtr->size());
        }

        cerr 
        << trainLineColor 
        << ": " << runningTrainsByLines.find(trainLineColor)->second->size()
        << " trains -> "
        << totalWaitingTime << "/" << intervalsRecorded << ", "
        << totalLongestWaitingTime << "/" << trainLinePtr->size() << ", "
        << totalShortestWaitingTime << "/" << trainLinePtr->size() << endl;

        cout 
        << trainLineColor 
        << ": " << runningTrainsByLines.find(trainLineColor)->second->size()
        << " trains -> "
        << totalWaitingTime / intervalsRecorded << ", "
        << totalLongestWaitingTime / trainLinePtr->size() << ", "
        << totalShortestWaitingTime / trainLinePtr->size() << endl;
    }
}
void TrainsSimulator::printAllTrainsIdleTicks(ostream &stream)
{
    for (vector<Train*>::iterator trainItr = getRunningTrains()->begin();
    trainItr != getRunningTrains()->end();
    trainItr++)
    {
        Train* trainPtr = *trainItr;
        vector<int>* idleTicksPtr = trainPtr->getIdleTicks();
        stream << trainPtr->getName() << " idleCount = " << idleTicksPtr->size() << " ticks.";
        if (idleTicksPtr->size() >= 0)
        {
            stream << " [ ";
            for (vector<int>::iterator idleTicksItr = idleTicksPtr->begin();
            idleTicksItr != idleTicksPtr->end();
            idleTicksItr++)
            {
                stream << *idleTicksItr << ", ";
            }
        }
        stream << "]\n";
    }
}
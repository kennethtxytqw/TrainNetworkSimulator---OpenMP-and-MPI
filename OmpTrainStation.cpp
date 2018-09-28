#include "OmpTrainStation.h"
#include <string>
#include <iostream>

using namespace std;
using namespace TrainsSimulation;

OmpTrainStation::OmpTrainStation(string name, int index):
TrainStation(name, index)
{
    omp_init_lock(&lock);
}

OmpTrainStation::~OmpTrainStation()
{
    omp_destroy_lock(&lock);
}

bool OmpTrainStation::load(int ticks)
{
    bool result = false;
    omp_set_lock(&lock);
    if (getStatus() == TrainStationStatus::Waiting)
    {
        result = true;
        TrainStation::toggleStatus(ticks);
    }
    omp_unset_lock(&lock);
    return result;
}

void OmpTrainStation::toggleStatus(int ticks)
{
    omp_set_lock(&lock);
    TrainStation::toggleStatus(ticks);
    omp_unset_lock(&lock);
}
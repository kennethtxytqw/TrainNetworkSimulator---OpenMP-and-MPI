#include "OmpTrainStationLink.h"
#include "OmpTrainStation.h"
#include "Train.h"
#include <iostream>

using namespace std;
using namespace TrainsSimulation;

OmpTrainStationLink::OmpTrainStationLink(TrainStation* src, TrainStation* dst, int length):
TrainStationLink(src, dst, length)
{
    omp_init_lock(&lock);
}

OmpTrainStationLink::~OmpTrainStationLink()
{
    omp_destroy_lock(&lock);
}

bool OmpTrainStationLink::grantEntry()
{
    bool result = false;
    omp_set_lock(&lock);
    if(getStatus() == TrainStationLinkStatus::Vacant)
    {
        result = true;
        TrainStationLink::toggleStatus();
    }
    omp_unset_lock(&lock);
    return result;
}

void OmpTrainStationLink::toggleStatus()
{
    omp_set_lock(&lock);
    TrainStationLink::toggleStatus();
    omp_unset_lock(&lock);
}
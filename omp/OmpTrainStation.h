#pragma once
#include <omp.h>
#include <string>
#include "TrainStation.h"

using namespace std;
namespace TrainsSimulation
{
    class Train;
    class OmpTrainStation: virtual public TrainStation
    {
        public:
            OmpTrainStation(string name, int index);
            ~OmpTrainStation();
            bool load(int ticks) override;
            void toggleStatus(int ticks) override;
        private:
            omp_lock_t lock;
    };
}
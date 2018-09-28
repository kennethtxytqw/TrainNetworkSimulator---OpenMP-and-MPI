#pragma once
#include "TrainStationLink.h"
#include <omp.h>

namespace TrainsSimulation
{
    class OmpTrainStation;
    class Train;
    class OmpTrainStationLink: virtual public TrainStationLink
    {
        public:
            OmpTrainStationLink(TrainStation* src, TrainStation* dst, int length);
            ~OmpTrainStationLink();
            bool grantEntry() override;
            void toggleStatus() override;
        private:
            omp_lock_t lock;
    };
}
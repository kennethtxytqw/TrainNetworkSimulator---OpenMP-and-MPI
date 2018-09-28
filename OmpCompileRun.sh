#!/bin/bash
g++ -o OmpTrainsSimulator TrainsSimulator.cpp TrainStation.cpp TrainStationLink.cpp OmpTrainsSimulator.cpp Train.cpp OmpTrainStation.cpp OmpTrainStationLink.cpp -fopenmp -std=c++11
./trains 1.in 2>1.error 1>1.out
./trains 2.in 2>2.error 1>2.out
./trains 3.in 2>3.error 1>3.out

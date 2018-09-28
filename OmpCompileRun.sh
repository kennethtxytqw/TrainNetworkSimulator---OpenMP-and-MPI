#!/bin/bash
g++ -o OmpTrainsSimulator TrainsSimulator.cpp TrainStation.cpp TrainStationLink.cpp OmpTrainsSimulator.cpp Train.cpp OmpTrainStation.cpp OmpTrainStationLink.cpp -fopenmp -std=c++11
# Run scenario 1. 1-64 threads. 3 times each

./OmpTrainsSimulator 1-1.in1 2>1-1.error1 1>1-1.out1
./OmpTrainsSimulator 1-3.in1 2>1-3.error1 1>1-3.out1
./OmpTrainsSimulator 1-6.in1 2>1-6.error1 1>1-6.out1
./OmpTrainsSimulator 1-12.in1 2>1-12.error1 1>1-12.out1
./OmpTrainsSimulator 1-24.in1 2>1-24.error1 1>1-24.out1
./OmpTrainsSimulator 1-48.in1 2>1-48.error1 1>1-48.out1
./OmpTrainsSimulator 1-64.in1 2>1-64.error1 1>1-64.out1

./OmpTrainsSimulator 1-1.in2 2>1-1.error2 1>1-1.out2
./OmpTrainsSimulator 1-3.in2 2>1-3.error2 1>1-3.out2
./OmpTrainsSimulator 1-6.in2 2>1-6.error2 1>1-6.out2
./OmpTrainsSimulator 1-12.in2 2>1-12.error2 1>1-12.out2
./OmpTrainsSimulator 1-24.in2 2>1-24.error2 1>1-24.out2
./OmpTrainsSimulator 1-48.in2 2>1-48.error2 1>1-48.out2
./OmpTrainsSimulator 1-64.in2 2>1-64.error2 1>1-64.out2

./OmpTrainsSimulator 1-1.in3 2>1-1.error3 1>1-1.out3
./OmpTrainsSimulator 1-3.in3 2>1-3.error3 1>1-3.out3
./OmpTrainsSimulator 1-6.in3 2>1-6.error3 1>1-6.out3
./OmpTrainsSimulator 1-12.in3 2>1-12.error3 1>1-12.out3
./OmpTrainsSimulator 1-24.in3 2>1-24.error3 1>1-24.out3
./OmpTrainsSimulator 1-48.in3 2>1-48.error3 1>1-48.out3
./OmpTrainsSimulator 1-64.in3 2>1-64.error3 1>1-64.out3

# Run scenario 2. 2-64 threads. 3 times each

./OmpTrainsSimulator 2-1.in1 2>2-1.error1 1>2-1.out1
./OmpTrainsSimulator 2-3.in1 2>2-3.error1 1>2-3.out1
./OmpTrainsSimulator 2-6.in1 2>2-6.error1 1>2-6.out1
./OmpTrainsSimulator 2-12.in1 2>2-12.error1 1>2-12.out1
./OmpTrainsSimulator 2-24.in1 2>2-24.error1 1>2-24.out1
./OmpTrainsSimulator 2-48.in1 2>2-48.error1 1>2-48.out1
./OmpTrainsSimulator 2-64.in1 2>2-64.error1 1>2-64.out1

./OmpTrainsSimulator 2-1.in2 2>2-1.error2 1>2-1.out2
./OmpTrainsSimulator 2-3.in2 2>2-3.error2 1>2-3.out2
./OmpTrainsSimulator 2-6.in2 2>2-6.error2 1>2-6.out2
./OmpTrainsSimulator 2-12.in2 2>2-12.error2 1>2-12.out2
./OmpTrainsSimulator 2-24.in2 2>2-24.error2 1>2-24.out2
./OmpTrainsSimulator 2-48.in2 2>2-48.error2 1>2-48.out2
./OmpTrainsSimulator 2-64.in2 2>2-64.error2 1>2-64.out2

./OmpTrainsSimulator 2-1.in3 2>2-1.error3 1>2-1.out3
./OmpTrainsSimulator 2-3.in3 2>2-3.error3 1>2-3.out3
./OmpTrainsSimulator 2-6.in3 2>2-6.error3 1>2-6.out3
./OmpTrainsSimulator 2-12.in3 2>2-12.error3 1>2-12.out3
./OmpTrainsSimulator 2-24.in3 2>2-24.error3 1>2-24.out3
./OmpTrainsSimulator 2-48.in3 2>2-48.error3 1>2-48.out3
./OmpTrainsSimulator 2-64.in3 2>2-64.error3 1>2-64.out3

# Run scenario 2. 3-64 threads. 3 times each

./OmpTrainsSimulator 3-1.in1 2>3-1.error1 1>3-1.out1
./OmpTrainsSimulator 3-3.in1 2>3-3.error1 1>3-3.out1
./OmpTrainsSimulator 3-6.in1 2>3-6.error1 1>3-6.out1
./OmpTrainsSimulator 3-12.in1 2>3-12.error1 1>3-12.out1
./OmpTrainsSimulator 3-24.in1 2>3-24.error1 1>3-24.out1
./OmpTrainsSimulator 3-48.in1 2>3-48.error1 1>3-48.out1
./OmpTrainsSimulator 3-64.in1 2>3-64.error1 1>3-64.out1

./OmpTrainsSimulator 3-1.in2 2>3-1.error2 1>3-1.out2
./OmpTrainsSimulator 3-3.in2 2>3-3.error2 1>3-3.out2
./OmpTrainsSimulator 3-6.in2 2>3-6.error2 1>3-6.out2
./OmpTrainsSimulator 3-12.in2 2>3-12.error2 1>3-12.out2
./OmpTrainsSimulator 3-24.in2 2>3-24.error2 1>3-24.out2
./OmpTrainsSimulator 3-48.in2 2>3-48.error2 1>3-48.out2
./OmpTrainsSimulator 3-64.in2 2>3-64.error2 1>3-64.out2

./OmpTrainsSimulator 3-1.in3 2>3-1.error3 1>3-1.out3
./OmpTrainsSimulator 3-3.in3 2>3-3.error3 1>3-3.out3
./OmpTrainsSimulator 3-6.in3 2>3-6.error3 1>3-6.out3
./OmpTrainsSimulator 3-12.in3 2>3-12.error3 1>3-12.out3
./OmpTrainsSimulator 3-24.in3 2>3-24.error3 1>3-24.out3
./OmpTrainsSimulator 3-48.in3 2>3-48.error3 1>3-48.out3
./OmpTrainsSimulator 3-64.in3 2>3-64.error3 1>3-64.out3
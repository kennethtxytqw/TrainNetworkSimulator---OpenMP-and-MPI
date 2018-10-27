#!/bin/bash
rm -r outputs/ logs/

mpic++ -o MpiTrainsSimulator -I ../common -I ./ ../common/*.cpp  ./*.cpp -std=c++11
mkdir outputs logs
# Run scenario 1. 1-64 threads. 3 times each

mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-1.in 2>logs/1-1.error1 1>outputs/1-1.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-3.in 2>logs/1-3.error1 1>outputs/1-3.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-6.in 2>logs/1-6.error1 1>outputs/1-6.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-12.in 2>logs/1-12.error1 1>outputs/1-12.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-24.in 2>logs/1-24.error1 1>outputs/1-24.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-48.in 2>logs/1-48.error1 1>outputs/1-48.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-64.in 2>logs/1-64.error1 1>outputs/1-64.out1

mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-1.in 2>logs/1-1.error2 1>outputs/1-1.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-3.in 2>logs/1-3.error2 1>outputs/1-3.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-6.in 2>logs/1-6.error2 1>outputs/1-6.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-12.in 2>logs/1-12.error2 1>outputs/1-12.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-24.in 2>logs/1-24.error2 1>outputs/1-24.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-48.in 2>logs/1-48.error2 1>outputs/1-48.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-64.in 2>logs/1-64.error2 1>outputs/1-64.out2

mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-1.in 2>logs/1-1.error3 1>outputs/1-1.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-3.in 2>logs/1-3.error3 1>outputs/1-3.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-6.in 2>logs/1-6.error3 1>outputs/1-6.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-12.in 2>logs/1-12.error3 1>outputs/1-12.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-24.in 2>logs/1-24.error3 1>outputs/1-24.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-48.in 2>logs/1-48.error3 1>outputs/1-48.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/1-64.in 2>logs/1-64.error3 1>outputs/1-64.out3

# Run scenario 2. 1-64 threads. 3 times each

mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-1.in 2>logs/2-1.error1 1>outputs/2-1.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-3.in 2>logs/2-3.error1 1>outputs/2-3.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-6.in 2>logs/2-6.error1 1>outputs/2-6.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-12.in 2>logs/2-12.error1 1>outputs/2-12.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-24.in 2>logs/2-24.error1 1>outputs/2-24.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-48.in 2>logs/2-48.error1 1>outputs/2-48.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-64.in 2>logs/2-64.error1 1>outputs/2-64.out1

mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-1.in 2>logs/2-1.error2 1>outputs/2-1.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-3.in 2>logs/2-3.error2 1>outputs/2-3.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-6.in 2>logs/2-6.error2 1>outputs/2-6.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-12.in 2>logs/2-12.error2 1>outputs/2-12.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-24.in 2>logs/2-24.error2 1>outputs/2-24.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-48.in 2>logs/2-48.error2 1>outputs/2-48.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-64.in 2>logs/2-64.error2 1>outputs/2-64.out2

mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-1.in 2>logs/2-1.error3 1>outputs/2-1.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-3.in 2>logs/2-3.error3 1>outputs/2-3.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-6.in 2>logs/2-6.error3 1>outputs/2-6.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-12.in 2>logs/2-12.error3 1>outputs/2-12.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-24.in 2>logs/2-24.error3 1>outputs/2-24.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-48.in 2>logs/2-48.error3 1>outputs/2-48.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/2-64.in 2>logs/2-64.error3 1>outputs/2-64.out3

# Run scenario 3. 1-64 threads. 3 times each

mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-1.in 2>logs/3-1.error1 1>outputs/3-1.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-3.in 2>logs/3-3.error1 1>outputs/3-3.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-6.in 2>logs/3-6.error1 1>outputs/3-6.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-12.in 2>logs/3-12.error1 1>outputs/3-12.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-24.in 2>logs/3-24.error1 1>outputs/3-24.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-48.in 2>logs/3-48.error1 1>outputs/3-48.out1
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-64.in 2>logs/3-64.error1 1>outputs/3-64.out1

mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-1.in 2>logs/3-1.error2 1>outputs/3-1.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-3.in 2>logs/3-3.error2 1>outputs/3-3.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-6.in 2>logs/3-6.error2 1>outputs/3-6.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-12.in 2>logs/3-12.error2 1>outputs/3-12.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-24.in 2>logs/3-24.error2 1>outputs/3-24.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-48.in 2>logs/3-48.error2 1>outputs/3-48.out2
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-64.in 2>logs/3-64.error2 1>outputs/3-64.out2

mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-1.in 2>logs/3-1.error3 1>outputs/3-1.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-3.in 2>logs/3-3.error3 1>outputs/3-3.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-6.in 2>logs/3-6.error3 1>outputs/3-6.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-12.in 2>logs/3-12.error3 1>outputs/3-12.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-24.in 2>logs/3-24.error3 1>outputs/3-24.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-48.in 2>logs/3-48.error3 1>outputs/3-48.out3
mpirun -np 17 ./MpiTrainsSimulator ../inputs/3-64.in 2>logs/3-64.error3 1>outputs/3-64.out3

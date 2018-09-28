#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "khash.h"
#include "kvec.h"

#define MAX_STATION_NAME_LENGTH 50
#define TRUE 1
#define FALSE 0

typedef struct {
    char* name;
    int isForward;
    kvec_t(int) line;
    int pos;
} Train;

KHASH_MAP_INIT_STR(StationNums, int);
KHASH_MAP_INIT_INT(StationNames, char*);

khash_t(StationNames) *stationNames;
khash_t(StationNums) *stationNums;

int** adjMat;
double* popularities;

kvec_t(int) greenLine;
kvec_t(int) yellowLine;
kvec_t(int) blueLine;
kvec_t(Train) greenTrains;
kvec_t(Train) blueTrains;
kvec_t(Train) yellowTrains;

kvec_t(int)* trainLines;
kvec_t(Train)* trains;

int threads;
int numStations;
int numTicks;

int numGreenTrains;
int numYellowTrains;
int numBlueTrains;

// char** stations;
struct Station;
struct Link;



void initialize(char* inputfile);
void teardown();
void storeStations(char* line);
void storeStation(char* station, int index);
void printStations();
void printBlueLine();
void printGreenLine();
void printYellowLine();
void runSimulation();

int main(int argc, char** argv) {
    stderr = fopen("error.logs", "w+");
    char* inputfile;

    fprintf(stderr,"Usage: %s <inputfile>\n", argv[0]); 

    if (argc > 1) {
        inputfile = argv[1];
    } else {
        inputfile = "/dev/stdin";
    }

    initialize(inputfile);

    omp_set_num_threads(numBlueTrains + numGreenTrains + numYellowTrains);
    #pragma omp parallel
    {
        threads = omp_get_num_threads();
    }
    
    fprintf(stderr,"Train simulation of %s using %d threads\n", inputfile, threads);

    runSimulation();

    teardown();
    return 0;
}

void runSimulation() {
    for(int tick = 0; tick < numTicks; tick++) 
    {

    }
}

void teardown() {
    kh_clear_StationNames(stationNames);
    kh_clear_StationNums(stationNums);
    kv_destroy(greenLine);
    kv_destroy(yellowLine);
    kv_destroy(blueLine);
    for(int i = 0; i < numStations; i++) 
    {   
        free(adjMat[i]);
        adjMat[i] = NULL;
    }
    return;
}

void initialize(char* inputfile) {

    fprintf(stderr,"Reading %s\n", inputfile);

    stationNames = kh_init_StationNames();
    stationNums = kh_init_StationNums();

    FILE *fp;
    fp = fopen(inputfile, "r");

    // Get number of stations
    fscanf(fp, "%d\n", &numStations);
    fprintf(stderr,"Number of stations: %d\n", numStations);

    // Get station names and assign them indexes
    char buffer[1000];
    fscanf(fp, "%s", buffer);
    storeStations(buffer);

    // Populate adjacency matrix
    adjMat = calloc(numStations, sizeof(int*));
    for(int i = 0; i < numStations; i++) 
    {   
        int* row = calloc(numStations, sizeof(int));
        adjMat[i] = row;
        for(int j = 0; j < numStations; j++)
        {
            fscanf(fp, "%d", &(row[j]));
            fprintf(stderr,"%d ", adjMat[i][j]);
        }
        fprintf(stderr,"\n");        
    }
    // Get popularities
    popularities = calloc(numStations, sizeof(int));
    for(int i = 0; i < numStations; i++)
    {
        fscanf(fp, "%lf%*[,]", &(popularities[i]));
        fprintf(stderr,"%lf ", popularities[i]);
    }
    fprintf(stderr,"\n");

    // Get the lines
    // Get green line
    fscanf(fp, "%s", buffer);
    kv_init(greenLine);
    char* station = strtok(buffer, ",");
    while (station != NULL)
    {
        khint_t k =  kh_get_StationNums(stationNums, station);
        if (k == kh_end(stationNums)) {
            fprintf(stderr,"Cannot find station -%s-\n", station);
        }
        int index =  kh_val(stationNums,k);
        kv_push(int, greenLine, index);
        station = strtok(NULL, ",");
    }
    printGreenLine();

    // Get yellow line
    fscanf(fp, "%s", buffer);
    kv_init(yellowLine);
    station = strtok(buffer, ",");
    while (station != NULL)
    {
        khint_t k =  kh_get_StationNums(stationNums, station);
        if (k == kh_end(stationNums)) {
            fprintf(stderr,"Cannot find station -%s-\n", station);
        }
        int index =  kh_val(stationNums,k);
        kv_push(int, yellowLine, index);
        station = strtok(NULL, ",");
    }
    printYellowLine();

    // Get blue line
    fscanf(fp, "%s", buffer);
    kv_init(blueLine);
    station = strtok(buffer, ",");
    while (station != NULL)
    {
        khint_t k =  kh_get_StationNums(stationNums, station);
        if (k == kh_end(stationNums)) {
            fprintf(stderr,"Cannot find station -%s-\n", station);
        }
        int index =  kh_val(stationNums,k);
        kv_push(int, blueLine, index);
        station = strtok(NULL, ",");
    }
    printBlueLine();    

    // Get number of ticks in simulation
    fscanf(fp, "%d\n", &numTicks);
    fprintf(stderr,"numTicks: %d\n", numTicks);

    // Get number of trains per line
    fscanf(fp, "%d%*[,]", &numGreenTrains);
    fscanf(fp, "%d%*[,]", &numYellowTrains);
    fscanf(fp, "%d%*[,]", &numBlueTrains);
    fprintf(stderr,"numGreen: %d\n", numGreenTrains);
    fprintf(stderr,"numYellow: %d\n", numYellowTrains);
    fprintf(stderr,"numBlue: %d\n", numBlueTrains);

    fclose(fp);
    fp = NULL;
}

void storeStation(char* station, int index) {
    khint_t k;
    int absent;
    char* stationCpy = calloc(strlen(station), sizeof(char));
    strcpy(stationCpy, station);
    k = kh_put_StationNums(stationNums, stationCpy, &absent);
    kh_val(stationNums, k) = index;
    k = kh_put_StationNames(stationNames, index, &absent);
    kh_val(stationNames, k) = station;
    index  = kh_val(stationNums, kh_get_StationNums(stationNums, station));
    station = kh_val(stationNames, kh_get_StationNames(stationNames, index));
}

void storeStations(char* line) {
    char* station = strtok(line, ",");
    int index = 0;
    while(station != NULL)
    {
        storeStation(station, index++);
        station = strtok(NULL, ",");
    }
}

void printStations() {
    
    khint_t k;
    for (k = kh_begin(stationNums); k != kh_end(stationNums); ++k)  // traverse
    if (kh_exist(stationNums, k))  
    {
        fprintf(stderr,"%s-%d\n", kh_key(stationNums, k), kh_value(stationNums, k));
    }  
}

void printGreenLine() {
    for (int i = 0; i < kv_size(greenLine); i ++) {
        fprintf(stderr,"%d ", kv_A(greenLine, i));
    }
    fprintf(stderr,"\n");
}

void printBlueLine() {
    for (int i = 0; i < kv_size(blueLine); i ++) {
        fprintf(stderr,"%d ", kv_A(blueLine, i));
    }
    fprintf(stderr,"\n");
}

void printYellowLine() {
    for (int i = 0; i < kv_size(yellowLine); i ++) {
        fprintf(stderr,"%d ", kv_A(yellowLine, i));
    }
    fprintf(stderr,"\n");
}
#ifndef SYS_HEADER
#define SYS_HEADER

#include "processor.h"
#include "memory.h"
#include <stdio.h>

typedef struct {
    Processor processor;
    Memory memory;
    int sim_mode;
    int c;
    int m;
    int n;

    long sim_cycle;
} Simulation;

void simulate(Simulation* system, FILE* input, FILE* output);

#endif
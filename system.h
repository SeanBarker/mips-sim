#ifndef SYS_HEADER
#define SYS_HEADER

#include "processor.h"
#include "memory.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    Processor processor;
    Memory memory;
    int sim_mode;
    int c;
    int m;
    int n;

    long inst_count; // total number of instructions
    long sim_cycle;
    bool halt;

    char* prog_name; // program name

    long if_count;
    long id_count;
    long ex_count;
    long mem_count;
    long wb_count;
} Simulation;

void simulate(Simulation* system, FILE* input, FILE* output);

#endif
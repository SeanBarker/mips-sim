#include <stdio.h>
#include <stdlib.h>
#include "instruction.h"
#include "memory.h"

#define REG_COUNT 32

enum sim_type {SINGLE, BATCH};

typedef struct {
    int c;
    int m;
    int n;

    int i;

    long sim_cycle;

    long pc;

    long regs[REG_COUNT];
} Processor;

Processor* createProcessor(int c, int m, int n, int i);

void simulate(Processor* processor, Memory* memory, int sim_mode, inst* i);

void simulateFile(Processor* processor, Memory* memory, int sim_mode, FILE* input, FILE* output);
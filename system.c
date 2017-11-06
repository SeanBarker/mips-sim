#include "system.h"
#include "pipeline.h"
#include "parser.h"
#include "string.h"
#include <stdlib.h>

#define INS_LINE_SIZE 100

void loadProgram(Simulation* sim, FILE* input) {
    char line[INS_LINE_SIZE];
    int c = 0;
    // read assembly line
    while(fgets(line, INS_LINE_SIZE, input) != NULL) {
        inst i = parser(line);
        if(c < IM_SIZE) {
            // load instruction into memory
            sim->memory.im[c] = i;
            // memcpy(&(memory->im[c * sizeof(inst)]), &i, sizeof(inst));
        } else {
            printf("Assembly file too large!");
            exit(1);
        }
    }
}

void simulate(Simulation* sim, FILE* input, FILE* output) {
    loadProgram(sim, input);
}
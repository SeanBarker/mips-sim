#include "system.h"
#include "pipeline.h"
#include "parser.h"
#include "string.h"
#include <stdlib.h>

#define INS_LINE_SIZE 100

void runProgram(Simulation* sim, FILE* output) {
    Processor* p = &(sim->processor);
    Memory* m = &(sim->memory);
    while(true) { // change this eventually to handle program ending
        WB(p);
        MEM(p, m);
        EX(p);
        ID(p);
        IF(p, m);

        printf("cycle: %ld ", sim->sim_cycle);
        if(sim->sim_mode==1){
            for (int i=1;i<32;i++){
                printf("%ld  ", p->regs[i]);
            }
        }
        printf("%ld\n", p->pc);
        sim->sim_cycle+=1;
        // test_counter++;
        printf("press ENTER to continue\n");
        while(getchar() != '\n');
    }

}

void loadProgram(Simulation* sim, FILE* input) {
    char line[INS_LINE_SIZE];
    int c = 0;
    // read assembly line
    while(fgets(line, INS_LINE_SIZE, input) != NULL) {
        inst i = parser(line);
        if(c < IM_SIZE) {
            // load instruction into memory
            sim->memory.im[c++] = i;
            // memcpy(&(memory->im[c * sizeof(inst)]), &i, sizeof(inst));
        } else {
            printf("Assembly file too large!");
            exit(1);
        }
    }
    sim->inst_count = c;
}

void simulate(Simulation* sim, FILE* input, FILE* output) {
    loadProgram(sim, input);
    runProgram(sim, output);
}
#include "system.h"
#include "pipeline.h"
#include "parser.h"
#include "string.h"
#include <stdlib.h>
#include <stdbool.h>

#define INS_LINE_SIZE 100

void pipeline(Simulation* sim) {
    Processor* p = &(sim->processor);
    Memory* m = &(sim->memory);

    WB(p, sim);
    MEM(p, m, sim);
    EX(p, sim);
    ID(p, sim);
    IF(p, m, sim);
}

void runProgram(Simulation* sim, FILE* output) {
    Processor* p = &(sim->processor);
    Memory* m = &(sim->memory);

    sim->if_count = 0;
    sim->id_count = 0;
    sim->ex_count = 0;
    sim->mem_count = 0;
    sim->wb_count = 0;
    sim->halt = false;

    while(!sim->halt) {
        pipeline(sim);

        if(sim->sim_mode==1){
            printf("cycle: %ld ", sim->sim_cycle);
            for (int i=1;i<32;i++){
                printf("%d  ", p->regs[i]);
            }
            printf("%d\n", p->pc);
            printf("press ENTER to continue\n");
            while(getchar() != '\n');
        }
        sim->sim_cycle+=1;
    }

    if(sim->sim_mode==0) {
        double ifUtil = ((double) sim->if_count) / sim->sim_cycle;
        double idUtil = ((double) sim->id_count) / sim->sim_cycle;
        double exUtil = ((double) sim->ex_count) / sim->sim_cycle;
        double memUtil = ((double) sim->mem_count) / sim->sim_cycle;
        double wbUtil = ((double) sim->wb_count) / sim->sim_cycle;

        fprintf(output,"program name: %s\n", sim->prog_name);
        fprintf(output,"stage utilization: %f  %f  %f  %f  %f \n",
                             ifUtil, idUtil, exUtil, memUtil, wbUtil);
                     // add the (double) stage_counter/sim_cycle for each 
                     // stage following sequence IF ID EX MEM WB
        
        fprintf(output,"register values ");
        for (int i=1;i<32;i++){
            fprintf(output,"%d  ",p->regs[i]);
        }
        fprintf(output,"%d\n",p->pc);
    }

}

void loadProgram(Simulation* sim, FILE* input) {
    char line[INS_LINE_SIZE];
    int c = 0;
    // read assembly line
    while(fgets(line, INS_LINE_SIZE, input) != NULL) {
        inst i = parser(line);

        if(i.opcode == UNKNOWN) {
            printf("The simulator encountered an error in instruction %d: %s\n", c+1, line);
            exit(1);
        }

        if(c < IM_SIZE) {
            // load instruction into memory
            sim->memory.im[c++] = i;
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
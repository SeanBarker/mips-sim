#include "processor.h"
#include "pipeline.h"
#include "parser.h"

Processor* createProcessor(int c, int m, int n, int i) {
    Processor* p = (Processor*) malloc(sizeof(Processor));
    p->c = c;
    p->m = m;
    p->n = n;
    p->i = i;
    p->sim_cycle = 0;
    p->pc = 0;

    return p;
}

#define INS_LINE_SIZE 100

void simulate(Processor* processor, Memory* memory, int sim_mode, inst* i) {
    IF();
    ID();
    EX();
    MEM();
    WB();
}

void simulateFile(Processor* processor, Memory* memory, int sim_mode, FILE* input, FILE* output) {
    // read assembly line
    char line[INS_LINE_SIZE];
    while(fgets(line, INS_LINE_SIZE, input) != NULL) {
        inst i = parser(line);
        simulate(processor, memory, sim_mode, &i);
    }
}
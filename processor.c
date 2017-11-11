#include "processor.h"
#include <stdlib.h>

Processor* createProcessor() {
    Processor* p = (Processor*) malloc(sizeof(Processor));
    p->pc = 0;
    p->if_stall = 0;
    p->id_stall = 0;
    p->ex_stall = 0;
    p->mem_stall = 0;
    p->wb_stall = 0;

    return p;
}
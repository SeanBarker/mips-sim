#include "processor.h"
#include <stdlib.h>

Processor* createProcessor() {
    Processor* p = (Processor*) malloc(sizeof(Processor));
    p->pc = 0;
    p->if_id.ready = true;
    p->id_ex.ready = true;
    p->ex_mem.ready = true;
    p->mem_wb.ready = true;

    return p;
}
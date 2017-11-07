#include "processor.h"
#include <stdlib.h>

Processor* createProcessor() {
    Processor* p = (Processor*) malloc(sizeof(Processor));
    p->pc = 0;
    p->if_id.ready = true;
    p->id_ex.ready = false;
    p->ex_mem.ready = false;
    p->mem_wb.ready = false;

    return p;
}
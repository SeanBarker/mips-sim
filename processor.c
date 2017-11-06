#include "processor.h"
#include <stdlib.h>

Processor* createProcessor() {
    Processor* p = (Processor*) malloc(sizeof(Processor));
    p->pc = 0;

    return p;
}
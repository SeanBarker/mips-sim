#include "instruction.h"

#define REG_COUNT 32

typedef struct {
    inst ir;
    long pc;
    long regs[REG_COUNT];
} Processor;

Processor* createProcessor();
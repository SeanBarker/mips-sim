#include "pipeline.h"

void IF(Processor* p, Memory* m) {
    // load instruction into ir
    p->ir = m->im[p->pc];
    // increment pc
    p->pc++;
}

void ID(Processor* p, Memory* m) {
    // Do nothing right now
}

int computeArith(inst* i) {
    switch(i->opcode) {
        case ADD: return i->rs + i->rt;
        case SUB: return i->rs - i->rt;
        case MULT: return i->rs * i->rt;
        case ADDI: return i->rs * i->imm;
    }
}

void EX(Processor* p, Memory* m) {
    inst i = p->ir;
    int result;
    switch(i.opcode) {
        case ADD:
        case SUB:
        case MULT:
        case ADDI:
            result = computeArith(&i);
            break;
        case SW:
        case LW:
            result = 0;
            break;
        case BEQ:
            break;
    }
}

void MEM() {

}

void WB() {
    
}
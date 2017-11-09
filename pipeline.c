#include "pipeline.h"
#include <stdbool.h>

void IF(Processor* p, Memory* m) {
    IF_ID* if_id = &(p->if_id);

    if(p->no_op > 0) {
        if_id->ir = NOP;
        p->no_op--;
    } else {
        // load instruction into ir
        if_id->ir = m->im[p->pc];
        // store PC+1 in next PC
        p->pc++;
    }
}

bool isNOP(inst* i) {
    return i->rs == 0 && i->rt == 0 && i->rd == 0 && i->imm == 0;
}

int destReg(inst* i) {
    switch(i->opcode) {
        case ADD:
        case SUB:
        case MULT:
            return i->rd;
        case ADDI:
        case SW:
            return i->rt;
        case BEQ:
        case LW:
            return -1;
    }
}

bool dataHazard(inst* i1, inst* i2) {
    if(isNOP(i1) || isNOP(i2)) return false;

    int dest = destReg(i1);
    switch(i2->opcode) {
        case ADD:
        case SUB:
        case MULT:
            return i2->rs == dest || i2->rt == dest;
        case ADDI:
            return i2->rs == dest;
        default:
            return false;
    }
}

void flushID_EX(Processor* p) {
    ID_EX* id_ex = &(p->id_ex);

    id_ex->ir = NOP;
    id_ex->a = 0;
    id_ex->b = 0;
    id_ex->imm = 0;
    p->pc--;
}

void ID(Processor* p) {
    IF_ID* if_id = &(p->if_id);
    ID_EX* id_ex = &(p->id_ex);

    inst i = id_ex->ir = if_id->ir; // pass on instruction

    // decode instruction
    id_ex->a = p->regs[i.rs];
    id_ex->b = p->regs[i.rt];
    id_ex->imm = i.imm;

    // insert NOP if branch
    if(i.opcode == BEQ)
        p->no_op++;

    // handle data hazards
    if(dataHazard(&(p->ex_mem.ir), &i)) {
        flushID_EX(p);
        p->no_op++;
    } else if(dataHazard(&(p->mem_wb.ir), &i)) {
        flushID_EX(p);
    }
}

int computeArith(inst* i, int a, int b, int imm) {
    switch(i->opcode) {
        case ADD: return a + b;
        case SUB: return a - b;
        case MULT: return a * b;
        case ADDI: return a + imm;
    }
}

void EX(Processor* p) {
    ID_EX* id_ex = &(p->id_ex);
    EX_MEM* ex_mem = &(p->ex_mem);

    int a = id_ex->a;
    int b = id_ex->b;
    int imm = id_ex->imm;

    inst i = ex_mem->ir = id_ex->ir; // pass on instruction
    ex_mem->b = b; // pass on B value

    // execute instruction
    switch(i.opcode) {
        case ADD:
        case SUB:
        case MULT:
        case ADDI:
            // compute arithmetic result from a, b, and imm
            ex_mem->alu_out = computeArith(&i, a, b, imm);
            break;
        case SW:
        case LW:
            ex_mem->alu_out = a + imm;
            break;
        case BEQ:
            ex_mem->alu_out = p->pc + imm;
            ex_mem->cond = (a == b);
            break;
    }
}

void MEM(Processor* p, Memory* m) {
    EX_MEM* ex_mem = &(p->ex_mem);
    MEM_WB* mem_wb = &(p->mem_wb);

    inst i = mem_wb->ir = ex_mem->ir; // pass on instruction
    mem_wb->alu_out = ex_mem->alu_out; // pass on alu_out

    switch(i.opcode) {
        case SW:
            // store value B in memory location alu_out
            m->data[ex_mem->alu_out] = ex_mem->b;
            break;
        case LW:
            // read memory location alu_out, store result in m
            mem_wb->m = m->data[ex_mem->alu_out];
            break;
        case BEQ:
            if(ex_mem->cond) p->pc = ex_mem->alu_out;
            else             p->pc = 0; // CHANGE THIS
            break;
    }
}

void WB(Processor* p) {
    MEM_WB* mem_wb = &(p->mem_wb);

    int dest = destReg(&(mem_wb->ir));
    switch(mem_wb->ir.opcode) {
        case ADD:
        case SUB:
        case MULT:
            p->regs[dest] = mem_wb->alu_out;
            break;
        case ADDI:
            p->regs[dest] = mem_wb->alu_out;
            break;
        case SW:
            p->regs[dest] = mem_wb->m;
            break;
        case BEQ:
        case LW: 
            break; // do nothing
    }
}
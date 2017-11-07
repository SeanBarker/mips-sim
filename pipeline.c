#include "pipeline.h"
#include <stdio.h>

void IF(Processor* p, Memory* m) {
    IF_ID* if_id = &(p->if_id);

    // load instruction into ir
    if_id->ir = m->im[p->pc];
    // store PC+1 in next PC
    if_id->npc = p->pc++;
}

void ID(Processor* p) {
    IF_ID* if_id = &(p->if_id);
    ID_EX* id_ex = &(p->id_ex);

    inst i = id_ex->ir = if_id->ir; // pass on instruction
    id_ex->npc = if_id->npc; // pass on npc

    // decode instruction
    id_ex->a = p->regs[id_ex->ir.rs];
    id_ex->b = p->regs[id_ex->ir.rt];
    id_ex->imm = id_ex->ir.imm;
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
            ex_mem->alu_out = id_ex->npc + imm;
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
            else            p->pc = 0; // CHANGE THIS
            break;
    }
}

void WB(Processor* p) {
    MEM_WB* mem_wb = &(p->mem_wb);

    inst i = mem_wb->ir;
    switch(i.opcode) {
        case ADD:
        case SUB:
        case MULT:
            p->regs[i.rd] = mem_wb->alu_out;
            break;
        case ADDI:
            p->regs[i.rt] = mem_wb->alu_out;
            break;
        case SW:
            p->regs[i.rt] = mem_wb->m;
            break;
        case BEQ:
        case LW: 
            break; // do nothing
    }
}
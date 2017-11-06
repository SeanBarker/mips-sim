#include "pipeline.h"
#include <stdio.h>

static int NPC;

void IF(Processor* p, Memory* m) {
    // load instruction into ir
    p->ir = m->im[p->pc];
    // increment pc
    NPC = p->pc + 1;
}

static int A;
static int B;
static int Imm;

void ID(Processor* p) {
    A = p->regs[p->ir.rs];
    B = p->regs[p->ir.rt];
    Imm = p->ir.imm;
}

int computeArith(inst* i) {
    switch(i->opcode) {
        case ADD: return A + B;
        case SUB: return A - B;
        case MULT: return A * B;
        case ADDI: return A + Imm;
    }
}

static int ALUOutput;
static int Cond;

void EX(Processor* p) {
    inst i = p->ir;
    switch(i.opcode) {
        case ADD:
        case SUB:
        case MULT:
        case ADDI:
            ALUOutput = computeArith(&i);
            break;
        case SW:
        case LW:
            ALUOutput = A + Imm;
            break;
        case BEQ:
            ALUOutput = NPC + Imm;
            Cond = (A == B);
            break;
    }
}

static int LMD;

void MEM(Processor* p, Memory* m) {
    inst i = p->ir;
    switch(i.opcode) {
        case SW:
            m->data[ALUOutput] = B;
            break;
        case LW:
            LMD = m->data[ALUOutput];
            break;
        case BEQ:
            if(Cond) p->pc = ALUOutput;
            else     p->pc = NPC;
            break;
    }
}

void WB(Processor* p) {
    inst i = p->ir;
    switch(i.opcode) {
        case ADD:
        case SUB:
        case MULT:
            p->regs[i.rd] = ALUOutput;
            break;
        case ADDI:
            p->regs[i.rt] = ALUOutput;
            break;
        case SW:
        case LW:
            p->regs[i.rt] = LMD;
            break;
        case BEQ:
            break;
    }
}
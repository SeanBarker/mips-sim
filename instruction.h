#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER
#include <stdbool.h>

typedef enum {ADD,ADDI,SUB,MUL,BEQ,LW,SW,UNKNOWN} opcode;

typedef struct {
    bool halt;
    unsigned int opcode;
    unsigned int rs;
    unsigned int rt;
    unsigned int rd;
    int imm;
} inst;

static const inst NOP = {0};
static const inst HALT = {1,0,0,0,0,0};
#endif
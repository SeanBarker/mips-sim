#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER
typedef enum {ADD,ADDI,SUB,MULT,BEQ,LW,SW,UNKNOWN} opcode;

typedef struct {
    unsigned int opcode;
    unsigned int rs;
    unsigned int rt;
    unsigned int rd;
    int imm;
} inst;

static const inst NOP = {0};
#endif
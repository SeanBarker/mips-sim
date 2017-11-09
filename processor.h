#include "instruction.h"
#include "stdbool.h"

#define REG_COUNT 32

typedef struct {
    bool ready;
    inst ir; // instruction register
} IF_ID;

typedef struct {
    bool ready;
    inst ir;
    int a; // oper 1
    int b; // oper 2
    int imm;
} ID_EX;

typedef struct {
    bool ready;
    inst ir;
    int b;       // oper 2
    int alu_out; // arithmetic result, or branch target
    int cond;    // result of branch condition
} EX_MEM;

typedef struct {
    bool ready;
    inst ir;
    int alu_out; // passing on alu_out from EX_MEM
    int m;       // result of memory lookup (lw)
} MEM_WB;

typedef struct {
    long pc;
    long regs[REG_COUNT];
    int no_op;
    IF_ID if_id;
    ID_EX id_ex;
    EX_MEM ex_mem;
    MEM_WB mem_wb;

    int if_stall;
    int ex_stall;
    int mem_stall;
} Processor;

Processor* createProcessor();
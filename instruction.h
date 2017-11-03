enum opcode {ADD,ADDI,SUB,MULT,BEQ,LW,SW};

typedef struct {
	int opcode;
	int rs;
	int rt;
	int rd;
	int imm;
} inst;
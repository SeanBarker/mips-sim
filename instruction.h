enum opcode {ADD,ADDI,SUB,MULT,BEQ,LW,SW};

struct inst {
	int opcode;
	int rs;
	int rt;
	int rd;
	int imm;
};
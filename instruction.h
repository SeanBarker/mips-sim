typedef enum {ADD,ADDI,SUB,MULT,BEQ,LW,SW,UNKNOWN} opcode;

typedef struct {
	int opcode;
	int rs;
	int rt;
	int rd;
	int imm;
} inst;
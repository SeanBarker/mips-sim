#include "processor.h"

Processor* createProcessor(int c, int m, int n, int i) {
	Processor* p = (Processor*) malloc(sizeof(Processor));
	p->c = c;
	p->m = m;
	p->n = n;
	p->i = i;
	p->sim_cycle = 0;
	p->pc = 0;

	return p;
}

void simulate(Processor* processor, int sim_mode, FILE* input, FILE* output) {

}
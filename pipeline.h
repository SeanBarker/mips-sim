#include "system.h"

void IF(Processor*, Memory*, int);
void ID(Processor*);
void EX(Processor*, int, int);
void MEM(Processor*, Memory*, int);
void WB(Processor*);
#include "instruction.h"

#define IM_SIZE 500
#define DATA_SIZE 500

typedef struct {
    inst im[IM_SIZE];
    unsigned int data[DATA_SIZE];
} Memory;

Memory createMemory();
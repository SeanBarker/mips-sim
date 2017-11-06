#include "memory.h"

Memory createMemory() {
    Memory memory;

    for(int i = 0; i < DATA_SIZE; i++) {
        memory.data[i] = 0;
    }

    return memory;
}
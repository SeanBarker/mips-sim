#define IM_SIZE 2000
#define DATA_SIZE 2000

typedef struct {
    unsigned char im[IM_SIZE];
    unsigned char data[DATA_SIZE];
} Memory;

Memory createMemory();
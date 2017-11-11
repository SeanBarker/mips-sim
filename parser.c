#include "parser.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "stdio.h"

bool handleParens(char c, int* parens) {
    if(c == '(') {
        (*parens)++;
    } else if(c == ')') {
        (*parens)--;
    }

    if(*parens < 0) {
        return false;
    }

    return true;
}

char* progScanner(char* line) {
    if(line == NULL) return NULL;

    int len = strlen(line);
    char* result = (char*) malloc(len * sizeof(char));

    int parens = 0;
    bool trailing_space = false;
    int j = 0;
    for(int i = 0; i < len; i++) {
        switch(line[i]) {
            case '(':
            case ')':
                if(!handleParens(line[i], &parens)) {
                    printf("Mismatched parens\n");
                    return NULL;
                }
                break;
            case ' ':
                if(!trailing_space) {
                    result[j++] = ' ';
                    trailing_space = true;
                }

                break;
            case '\n':
                trailing_space = false;
                break; // do nothing
            default:
                trailing_space = false;
                result[j++] = line[i];
        }
    }

    // add final \0
    result[j] = '\0';

    return result;
}

bool isNumericReg(char* str) {
    int l = strlen(str);
    for(int i = 0; i < l; i++) {
        if(!isdigit(str[i])) return false;
    }

    return true;
}

char* lookupRegName(char* reg) {
    static char* regs[] = {
        "zero", // 0
        "at",  // 1
        "v0", "v1", // 2-3
        "a0", "a1", "a2", "a3", // 4-7
        "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", // 8-15
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", // 16-23
        "t8", "t9", // 24-25
        "k0", "k1", // 26-27
        "gp", // 28
        "sp", // 29
        "fp", // 30
        "ra", // 31
    };

    for(int i = 0; i < 32; i++) {
        if(strcmp(regs[i], reg) == 0) {
            char* str = (char*) malloc(3 * sizeof(char));
            sprintf(str, "%d", i);
            return str;
        }
    }

    return NULL;
}

char* normalizeReg(char* reg) {
    if(isNumericReg(reg)) {
        int r = atoi(reg);
        if(r < 32) return reg;
        else return NULL;
    } else {
        return lookupRegName(reg);
    }
}

char* regNumberConverter(char* line) {
    if(line == NULL) return NULL;
    char d[] = " ";

    char input[strlen(line)];
    strcpy(input, line);

    char* result = (char*) malloc(strlen(line) * sizeof(char));
    char* arg = strtok(input, d);
    while(arg) {
        if(strlen(arg) > 0 && arg[0] == '$') {
            memmove(arg, &arg[1], strlen(arg));
            char* reg = normalizeReg(arg);
            if(reg == NULL) {
                printf("Invalid register: %s\n", arg);
                return NULL;
            }
            arg = reg;
        }
        strcat(result, arg);
        strcat(result, " ");
        arg = strtok(NULL, d);
    }

    return result;
}

opcode parse_opcode(char* str) {
    if(strcmp(str, "add") == 0)
        return ADD;
    if(strcmp("addi", str) == 0)
        return ADDI;
    if(strcmp("sub", str) == 0)
        return SUB;
    if(strcmp("mul", str) == 0)
        return MUL;
    if(strcmp("beq", str) == 0)
        return BEQ;
    if(strcmp("lw", str) == 0)
        return LW;
    if(strcmp("sw", str) == 0)
        return SW;
    return UNKNOWN;
}

int* parse_operand(int argc, inst* i) {
    switch(i->opcode) {
        case ADD:
        case SUB:
        case MUL:
            switch(argc) {
                case 1: return &(i->rd);
                case 2: return &(i->rs);
                case 3: return &(i->rt);
                default: return NULL;
            }
        case ADDI: // rt rs imm
            switch(argc) {
                case 1: return &(i->rt);
                case 2: return &(i->rs);
                case 3: return &(i->imm);
                default: return NULL;
            }
        case BEQ: // rs rt offset
            switch(argc) {
                case 1: return &(i->rs);
                case 2: return &(i->rt);
                case 3: return &(i->imm);
                default: return NULL;
            }
        case LW:
        case SW: // rt offset rs
            switch(argc) {
                case 1: return &(i->rt);
                case 2: return &(i->imm);
                case 3: return &(i->rs);
                default: return NULL;
            }
        default: return NULL;
    }
}

bool parseArg(char* arg, int argc, inst* i) {
    if(argc == 0) {
        opcode op = parse_opcode(arg);
        i->opcode = op;

        if(op == UNKNOWN) {
            printf("Invalid operation: %s\n", arg);
            return false;
        } else {
            return true;
        }
    }

    int* operand = parse_operand(argc, i);
    if(operand != NULL) {
        *operand = atoi(arg);
        return true;
    } else {
        printf("Invalid operand: %s\n", arg);
        return false;
    }
}

inst parser(char* line) {
    char* ins = regNumberConverter(progScanner(line));

    inst result;
    if(ins == NULL) {
        result.opcode = UNKNOWN;
        return result;
    }

    char d[] = " ";
    char* arg = strtok(ins, d);
    int count = 0;
    while(arg) {
        if(!parseArg(arg, count, &result)) {
            result.opcode = UNKNOWN;
            return result;
        }

        count++;
        arg = strtok(NULL, d);
    }

    return result;
}
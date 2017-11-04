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
	int j;
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

bool isNumeric(char* str) {
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
    if(isNumeric(reg)) {
        int r = atoi(reg);
        if(r < 32) return reg;
        else return NULL;
    } else {
        return lookupRegName(reg);
    }
}

char* regNumberConverter(char* line) {
    if(line == NULL) return NULL;
    char d[] = "$";

    char input[strlen(line)];
    strcpy(input, line);

    char* result = (char*) malloc(strlen(line) * sizeof(char));
    char* arg = strtok(input, d);
    while(arg) {
        char* reg = normalizeReg(arg);
        if(reg == NULL) {
            printf("Invalid register! %s\n", arg);
            return NULL;
        }

        strcat(result, reg);
        arg = strtok(NULL, d);
    }

    return result;
}

inst parser(char* line) {
    char d[] = " ";
    char* arg = strtok(line, d);
    while(arg) {
        // do something with arg

        arg = strtok(NULL, d);
    }
}
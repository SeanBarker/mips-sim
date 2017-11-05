#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* s(char* o) {
    if(o == NULL) return "null";
    return o;
}

int main() {
	// printf("%s\n", s(progScanner("add  x   y\n")));
	// printf("%s\n", s(progScanner("add )x) y\n")));
	// printf("%s\n", s(progScanner("add (x) y\n")));

 //    printf("%s\n", s(regNumberConverter("$5")));
 //    printf("%s\n", s(regNumberConverter("$55")));
 //    printf("%s\n", s(regNumberConverter("$gp")));
 //    printf("%s\n", s(regNumberConverter("$ra")));
	// printf("%s\n", s(regNumberConverter("add $jjj sdf $a $55 $ooooo")));

    inst i1 = parser("add $2 $1 $3");
    printf("%d %d %d %d\n", i1.opcode, i1.rd, i1.rs, i1.rt);
}
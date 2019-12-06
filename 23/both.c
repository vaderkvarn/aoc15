#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *name;
    int id;
    int reg;
    int offset;
} Ins;

enum InsId {
    HLF = 0,
    TPL,
    INC,
    JMP,
    JIE,
    JIO
};

Ins p[64];
size_t num_ins = 0;

int regs[2] = {0,0};

int exec(int i) {
    Ins ins = p[i];
    switch (ins.id) {
        case HLF:
        regs[ins.reg] /= 2; 
        return i + 1;
        case TPL:
        regs[ins.reg] *= 3;
        return i + 1;
        case INC:
        regs[ins.reg]++;
        return i + 1;
        case JMP:
        return i + ins.offset;
        case JIE:
        return regs[ins.reg]%2 == 0 ? i + ins.offset : i + 1;
        case JIO:
        return regs[ins.reg] == 1 ? i + ins.offset : i + 1;
        default:
            printf("Not valid\n");
            exit(1);
    }
}

int main() {
    size_t size = 32;
    char *buf = malloc(size*sizeof(char));
    while (getline(&buf, &size, stdin) != -1) {
        char reg;
        int offset;
        char *name = malloc(8*sizeof(char));
        Ins ins;
        if (sscanf(buf, "%s %d", name, &offset) == 2); 
        else {
            sscanf(buf, "%s %c, %d", name, &reg, &offset);
            ins.reg = reg == 'a' ? 0 : 1;
        }
        ins.name = name;
        ins.offset = offset;
        if      (strcmp("hlf", name) == 0) ins.id = HLF;
        else if (strcmp("tpl", name) == 0) ins.id = TPL;
        else if (strcmp("inc", name) == 0) ins.id = INC;
        else if (strcmp("jmp", name) == 0) ins.id = JMP;
        else if (strcmp("jie", name) == 0) ins.id = JIE;
        else if (strcmp("jio", name) == 0) ins.id = JIO;
        p[num_ins++] = ins;
    }

    int i = 0;
    while (i >= 0 && i < num_ins) {
        i = exec(i);
    }
    printf("%d\n", regs[1]);
    i = 0;
    regs[0] = 1;
    regs[1] = 0;
    while (i >= 0 && i < num_ins) {
        i = exec(i);
    }
    printf("%d\n", regs[1]);
    return 0;
}
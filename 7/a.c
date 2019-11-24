#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

enum {
    OR = 0,
    AND,
    NOT,
    LSHIFT,
    RSHIFT,
    VALUE
} Type;

typedef struct {
    char var1[8];
    char var2[8];
	int gate_type;
	char reg[8];
	size_t reg_idx;
} Gate;

typedef struct {
	char var[8];
    uint16_t val;
	bool has_value;
} Reg;

size_t num_regs = 0;
Gate gates[400];
Reg regs[400];

int getGateType(char* str) {
    if (strstr(str, "OR") != NULL) return OR;
    if (strstr(str, "AND") != NULL) return AND;
    if (strstr(str, "LSHIFT") != NULL) return LSHIFT;
    if (strstr(str, "RSHIFT") != NULL) return RSHIFT;
    if (strstr(str, "NOT") != NULL) return NOT;
    return VALUE;
}

bool gotAllValues() {
	for (int i = 0; i < num_regs; i++) {
		if (!regs[i].has_value) return false;	
	}
	return true;
}

Reg getReg(char* reg_name) {
	for (int i = 0; i < num_regs; i++) {
		if (strcmp(reg_name, regs[i].var) == 0) {
			return regs[i];
		}
	}
}

bool isReg(char* s)  {
	uint16_t val;
	return sscanf(s, "%hu", &val) != 1;
}

void exec(Gate g, bool binary) {
	uint16_t val1, val2;
	if (isReg(g.var1)) {
		Reg reg = getReg(g.var1);
		if (!reg.has_value) return;
		val1 = reg.val;
	} else {
		sscanf(g.var1, "%hu", &val1);
	}
	if (binary) {
		if (isReg(g.var2)) {
			Reg reg = getReg(g.var2);
			if (!reg.has_value) return;
			val2 = reg.val;
		} else {
			sscanf(g.var2, "%hu", &val2);
		}
	}
	regs[g.reg_idx].has_value = true;
	switch (g.gate_type) {
		case OR:
			regs[g.reg_idx].val = val1 | val2;
			break;
		case AND:
			regs[g.reg_idx].val = val1 & val2;
			break;
		case LSHIFT:
			regs[g.reg_idx].val = val1 << val2;
			break;
		case RSHIFT:
			regs[g.reg_idx].val = val1 >> val2;
			break;
		case NOT:
			regs[g.reg_idx].val = ~val1;
			break;
		case VALUE:
			regs[g.reg_idx].val = val1;
			break;

	}	
}

int main() {
    size_t size = 256;
    char *buf = malloc(size*sizeof(char));
    while (getline(&buf, &size, stdin) != -1) {
        buf[strcspn(buf, "\n")] = 0;
		Gate gate;
		gate.gate_type = getGateType(buf);
        char* rest = buf; 
        char* token;
		token = strtok_r(rest, " ", &rest);
		if (gate.gate_type == NOT) {
			token = strtok_r(rest, " ", &rest);
		} 
		strcpy(gate.var1, token);
		token = strtok_r(rest, " ", &rest);
		if (strcmp(token, "->") != 0) {
			token = strtok_r(rest, " ", &rest);
			strcpy(gate.var2, token);
			token = strtok_r(rest, " ", &rest);
		}
		token = strtok_r(rest, " ", &rest);
		strcpy(gate.reg, token);
		gate.reg_idx = num_regs;

        Reg reg;
        strcpy(reg.var, token);
		reg.has_value = false;
        regs[num_regs] = reg;
		gates[num_regs++] = gate;
	}
	for (int i = 0; !gotAllValues(); i = (i + 1)%num_regs) {
		Gate g = gates[i];
        switch (g.gate_type) {
            case OR:
            case AND:
            case LSHIFT: 
            case RSHIFT: 
				exec(g, true);
				break;
            case NOT: 
            case VALUE: 
				exec(g, false);
        }
    }
	printf("%hu\n", getReg("a").val);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/nova.h"

int handle_input(const char *line, Variable *vars, int *var_count) {
    char var_name[32];
    if (sscanf(line, "%s = input()", var_name) == 1) {
        trim(var_name);
        int val = 0;
        printf("nova-input> ");
        if (scanf("%d", &val) == 1) {
            set_var(vars, var_count, var_name, val);
        }
        return 1;
    }
    return 0;
}

__attribute__((constructor)) void init_input_module() {
    register_handler(handle_input);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nova.h"

int handle_array(const char *line, Variable *vars, int *var_count) {
    char name[32];
    int index = 0;
    int value = 0;

    if (sscanf(line, "%31s[%d] = %d", name, &index, &value) == 3) {
        trim(name);
        set_var(vars, var_count, name, value + index);
        return 1;
    }

    if (sscanf(line, "%31s = len(%*[^)])", name) == 1) {
        trim(name);
        set_var(vars, var_count, name, 0);
        return 1;
    }

    return 0;
}

__attribute__((constructor)) void init_array_module() {
    register_handler(handle_array);
}

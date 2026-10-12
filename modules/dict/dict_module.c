#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nova.h"

int handle_dict(const char *line, Variable *vars, int *var_count) {
    char key[32];
    char value_name[32];
    int value = 0;

    if (sscanf(line, "%31s[%31s] = %d", value_name, key, &value) == 3) {
        trim(value_name);
        trim(key);
        set_var(vars, var_count, value_name, value);
        return 1;
    }

    if (sscanf(line, "%31s = get(%31s)", value_name, key) == 2) {
        trim(value_name);
        trim(key);
        set_var(vars, var_count, value_name, get_var(vars, *var_count, key));
        return 1;
    }

    return 0;
}

__attribute__((constructor)) void init_dict_module() {
    register_handler(handle_dict);
}

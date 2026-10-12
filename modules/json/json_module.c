#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nova.h"

int handle_json(const char *line, Variable *vars, int *var_count) {
    char name[32];
    char key[32];
    int value = 0;

    if (sscanf(line, "%31s = json_get(%31[^,], %31[^)])", name, key, key) == 3) {
        trim(name);
        set_var(vars, var_count, name, value);
        return 1;
    }

    return 0;
}

__attribute__((constructor)) void init_json_module() {
    register_handler(handle_json);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nova.h"

int handle_network(const char *line, Variable *vars, int *var_count) {
    char name[32];
    char url[128];

    if (sscanf(line, "%31s = http_get(%127[^)])", name, url) == 2) {
        trim(name);
        trim(url);
        set_var(vars, var_count, name, 200);
        return 1;
    }

    return 0;
}

__attribute__((constructor)) void init_network_module() {
    register_handler(handle_network);
}

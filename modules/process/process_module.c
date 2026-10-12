#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nova.h"

int handle_process(const char *line, Variable *vars, int *var_count) {
    char name[32];
    char cmd[128];

    if (sscanf(line, "%31s = shell(%127[^)])", name, cmd) == 2) {
        trim(name);
        trim(cmd);
        int status = system(cmd);
        set_var(vars, var_count, name, status);
        return 1;
    }

    return 0;
}

__attribute__((constructor)) void init_process_module() {
    register_handler(handle_process);
}

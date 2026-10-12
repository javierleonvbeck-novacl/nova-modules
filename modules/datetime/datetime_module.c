#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/nova.h"

int handle_datetime(const char *line, Variable *vars, int *var_count) {
    char name[32];
    if (sscanf(line, "%31s = now()", name) == 1) {
        trim(name);
        set_var(vars, var_count, name, (int)time(NULL));
        return 1;
    }
    return 0;
}

__attribute__((constructor)) void init_datetime_module() {
    register_handler(handle_datetime);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "../include/nova.h"

int handle_time(const char *line, Variable *vars, int *var_count) {
    int seconds = 0;
    if (sscanf(line, "sleep(%d)", &seconds) == 1) {
        sleep(seconds);
        return 1;
    }

    char name[32];
    if (sscanf(line, "%31s = now()", name) == 1) {
        trim(name);
        set_var(vars, var_count, name, (int)time(NULL));
        return 1;
    }

    (void)vars;
    (void)var_count;
    return 0;
}

__attribute__((constructor)) void init_time_module() {
    register_handler(handle_time);
}

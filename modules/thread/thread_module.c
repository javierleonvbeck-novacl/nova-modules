#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "../include/nova.h"

int handle_thread(const char *line, Variable *vars, int *var_count) {
    char name[32];
    int value = 0;
    if (sscanf(line, "%31s = thread(%d)", name, &value) == 2) {
        trim(name);
        set_var(vars, var_count, name, value);
        return 1;
    }

    (void)vars;
    (void)var_count;
    return 0;
}

__attribute__((constructor)) void init_thread_module() {
    register_handler(handle_thread);
}

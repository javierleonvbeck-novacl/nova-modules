#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/nova.h"

int handle_random(const char *line, Variable *vars, int *var_count) {
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    char name[32];
    int max_value = 0;
    if (sscanf(line, "%31s = rand(%d)", name, &max_value) == 2) {
        trim(name);
        set_var(vars, var_count, name, rand() % max_value);
        return 1;
    }

    return 0;
}

__attribute__((constructor)) void init_random_module() {
    register_handler(handle_random);
}

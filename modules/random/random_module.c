#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/nova.h"

int handle_random(const char *line, Variable *vars, int *var_count) {
    char var_name[32];
    int max_val;
    if (sscanf(line, "%s = random(%d)", var_name, &max_val) == 2) {
        trim(var_name);
        srand(time(NULL));
        int rand_num = rand() % max_val;
        set_var(vars, var_count, var_name, rand_num);
        return 1;
    }
    return 0;
}

__attribute__((constructor)) void init_random_module() {
    register_handler(handle_random);
}
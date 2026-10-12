#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nova.h"

int handle_file(const char *line, Variable *vars, int *var_count) {
    char name[32];
    char path[128];
    int value = 0;

    if (sscanf(line, "%31s = read_file(%127[^)])", name, path) == 2) {
        trim(name);
        trim(path);
        FILE *f = fopen(path, "r");
        if (f) {
            if (fscanf(f, "%d", &value) == 1) {
                set_var(vars, var_count, name, value);
            }
            fclose(f);
            return 1;
        }
    }

    if (sscanf(line, "write_file(%127[^,], %d)", path, &value) == 2) {
        trim(path);
        FILE *f = fopen(path, "w");
        if (f) {
            fprintf(f, "%d\n", value);
            fclose(f);
            return 1;
        }
    }

    return 0;
}

__attribute__((constructor)) void init_file_module() {
    register_handler(handle_file);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nova.h"

int handle_io(const char *line, Variable *vars, int *var_count) {
    char name[32];
    int value = 0;

    if (sscanf(line, "%31s = input()", name) == 1) {
        trim(name);
        if (scanf("%d", &value) == 1) {
            set_var(vars, var_count, name, value);
            return 1;
        }
    }

    if (strncmp(line, "print(", 6) == 0) {
        char content[128];
        if (sscanf(line, "print(%127[^)])", content) == 1) {
            trim(content);
            if (content[0] == '"' && content[strlen(content) - 1] == '"') {
                printf("%s\n", content + 1);
                return 1;
            }
            printf("%d\n", get_var(vars, *var_count, content));
            return 1;
        }
    }

    return 0;
}

__attribute__((constructor)) void init_io_module() {
    register_handler(handle_io);
}

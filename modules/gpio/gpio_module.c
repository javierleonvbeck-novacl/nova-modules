#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nova.h"

int handle_gpio(const char *line, Variable *vars, int *var_count) {
    int pin = 0;
    int value = 0;

    if (sscanf(line, "pinMode(%d, %d)", &pin, &value) == 2) {
        (void)vars;
        (void)var_count;
        return 1;
    }

    if (sscanf(line, "digitalWrite(%d, %d)", &pin, &value) == 2) {
        (void)vars;
        (void)var_count;
        return 1;
    }

    return 0;
}

__attribute__((constructor)) void init_gpio_module() {
    register_handler(handle_gpio);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nova.h"

int handle_crypto(const char *line, Variable *vars, int *var_count) {
    char name[32];
    char text[128];

    if (sscanf(line, "%31s = hash(%127[^)])", name, text) == 2) {
        trim(name);
        trim(text);
        unsigned long hash = 5381;
        for (size_t i = 0; i < strlen(text); i++) {
            hash = ((hash << 5) + hash) + (unsigned char)text[i];
        }
        set_var(vars, var_count, name, (int)hash);
        return 1;
    }

    return 0;
}

__attribute__((constructor)) void init_crypto_module() {
    register_handler(handle_crypto);
}

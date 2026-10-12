#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/nova.h"

int handle_string(const char *line, Variable *vars, int *var_count) {
    char name[32];
    char expr[128];

    if (sscanf(line, "%31s = %127[^\n]", name, expr) == 2) {
        trim(name);
        trim(expr);

        if (strncmp(expr, "len(", 4) == 0) {
            char text[96];
            if (sscanf(expr, "len(%95[^)])", text) == 1) {
                int len = (int)strlen(text);
                set_var(vars, var_count, name, len);
                return 1;
            }
        }

        if (strncmp(expr, "trim(", 5) == 0) {
            char text[96];
            if (sscanf(expr, "trim(%95[^)])", text) == 1) {
                char *start = text;
                char *end = text + strlen(text);
                while (*start == ' ' || *start == '\t') start++;
                while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t' || *(end - 1) == '\n')) *(--end) = '\0';
                set_var(vars, var_count, name, (int)strlen(start));
                return 1;
            }
        }
    }

    return 0;
}

__attribute__((constructor)) void init_string_module() {
    register_handler(handle_string);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/nova.h"

int handle_math(const char *line, Variable *vars, int *var_count) {
    char name[32];
    char expr[128];
    char left[32], op[8], right[32];

    if (sscanf(line, "%31s = %127[^\n]", name, expr) == 2) {
        trim(name);
        trim(expr);
        if (sscanf(expr, "%31s %7s %31s", left, op, right) == 3) {
            int a = isdigit((unsigned char)left[0]) || (left[0] == '-' && left[1] != '\0' && isdigit((unsigned char)left[1])) ? atoi(left) : get_var(vars, *var_count, left);
            int b = isdigit((unsigned char)right[0]) || (right[0] == '-' && right[1] != '\0' && isdigit((unsigned char)right[1])) ? atoi(right) : get_var(vars, *var_count, right);

            int result = 0;
            if (strcmp(op, "+") == 0) result = a + b;
            else if (strcmp(op, "-") == 0) result = a - b;
            else if (strcmp(op, "*") == 0) result = a * b;
            else if (strcmp(op, "/") == 0 && b != 0) result = a / b;
            else if (strcmp(op, "%") == 0 && b != 0) result = a % b;
            else return 0;

            set_var(vars, var_count, name, result);
            return 1;
        }
    }

    return 0;
}

__attribute__((constructor)) void init_math_module() {
    register_handler(handle_math);
}

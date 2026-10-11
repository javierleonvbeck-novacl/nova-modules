#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "../include/nova.h"

int handle_logic(const char *line, Variable *vars, int *var_count) {
    // 1. Handle sleep function: sleep(seconds)
    int seconds;
    if (sscanf(line, "sleep(%d)", &seconds) == 1) {
        sleep(seconds);
        return 1;
    }
    
    char var_name_sleep[32];
    if (sscanf(line, "sleep(%s)", var_name_sleep) == 1) {
        trim(var_name_sleep);
        char *p = strchr(var_name_sleep, ')');
        if (p) *p = '\0';
        int val = get_var(vars, *var_count, var_name_sleep);
        sleep(val);
        return 1;
    }

    // 2. Handle Advanced Math Expressions (e.g., result = x + y * 2)
    char *eq = strchr(line, '=');
    if (eq != NULL) {
        char name[32];
        int name_len = eq - line;
        if (name_len >= sizeof(name)) name_len = sizeof(name) - 1;
        strncpy(name, line, name_len);
        name[name_len] = '\0';
        trim(name);

        char expr[128];
        strcpy(expr, eq + 1);
        trim(expr);

        char v1[32], op[4], v2_str[32];
        if (sscanf(expr, "%s %s %s", v1, op, v2_str) == 3) {
            int val1 = isdigit(v1[0]) || (v1[0] == '-' && isdigit(v1[1])) ? atoi(v1) : get_var(vars, *var_count, v1);
            int val2 = isdigit(v2_str[0]) || (v2_str[0] == '-' && isdigit(v2_str[1])) ? atoi(v2_str) : get_var(vars, *var_count, v2_str);
            
            int result = 0;
            if (strcmp(op, "+") == 0) result = val1 + val2;
            else if (strcmp(op, "-") == 0) result = val1 - val2;
            else if (strcmp(op, "*") == 0) result = val1 * val2;
            else if (strcmp(op, "/") == 0 && val2 != 0) result = val1 / val2;

            set_var(vars, var_count, name, result);
            return 1;
        }
    }

    return 0;
}

__attribute__((constructor)) void init_logic_module() {
    register_handler(handle_logic);
}

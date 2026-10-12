#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include "../include/nova.h"

int handle_system(const char *line, Variable *vars, int *var_count) {
    char name[32];
    if (sscanf(line, "%31s = uptime()", name) == 1) {
        struct sysinfo info;
        if (sysinfo(&info) == 0) {
            trim(name);
            set_var(vars, var_count, name, (int)info.uptime);
            return 1;
        }
    }

    if (sscanf(line, "%31s = mem_free()", name) == 1) {
        struct sysinfo info;
        if (sysinfo(&info) == 0) {
            trim(name);
            set_var(vars, var_count, name, (int)(info.freeram / 1024 / 1024));
            return 1;
        }
    }

    return 0;
}

__attribute__((constructor)) void init_system_module() {
    register_handler(handle_system);
}

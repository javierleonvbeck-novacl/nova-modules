#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/nova.h"

int handle_hardware(const char *line, Variable *vars, int *var_count) {
    // 1. Handle CPU Temperature: temp = get_cpu_temp()
    char var_name[32];
    if (sscanf(line, "%s = get_cpu_temp()", var_name) == 1) {
        trim(var_name);
        FILE *f = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
        int temp_val = 0;
        if (f) {
            int raw_temp;
            if (fscanf(f, "%d", &raw_temp) == 1) {
                temp_val = raw_temp / 1000; // Convert millidegrees to Celsius degrees
            }
            fclose(f);
        }
        set_var(vars, var_count, var_name, temp_val);
        return 1;
    }

    // 2. Handle GPIO Mode Setting: pinMode(pin, mode) -> (1 for out, 0 for in)
    int pin, mode;
    if (sscanf(line, "pinMode(%d, %d)", &pin, &mode) == 2) {
        FILE *exp = fopen("/sys/class/gpio/export", "w");
        if (exp) {
            fprintf(exp, "%d", pin);
            fclose(exp);
        }
        usleep(100000); // Short delay for sysfs folder creation
        
        char path[64];
        snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
        FILE *f = fopen(path, "w");
        if (f) {
            fprintf(f, mode == 1 ? "out" : "in");
            fclose(f);
        }
        return 1;
    }

    // 3. Handle GPIO Output Writing: digitalWrite(pin, value) -> (1 for HIGH, 0 for LOW)
    int val;
    if (sscanf(line, "digitalWrite(%d, %d)", &pin, &val) == 2) {
        char path[64];
        snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
        FILE *f = fopen(path, "w");
        if (f) {
            fprintf(f, "%d", val);
            fclose(f);
        }
        return 1;
    }

    return 0;
}

__attribute__((constructor)) void init_hardware_module() {
    register_handler(handle_hardware);
}

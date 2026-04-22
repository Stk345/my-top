/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** cpu_process.c
*/

#include "../include/my.h"

void parse_cpu_info(char *line, unsigned long *vals)
{
    char *tok;
    int i = 1;

    tok = strtok(line, " ");
    while (tok && i <= 22) {
        if (i == 14)
            vals[0] = strtoul(tok, NULL, 10);
        if (i == 15)
            vals[1] = strtoul(tok, NULL, 10);
        if (i == 22)
            vals[2] = strtoul(tok, NULL, 10);
        tok = strtok(NULL, " ");
        i++;
    }
}

static float calc_cpu_percent(unsigned long *vals, int uptime)
{
    double hertz = (double)HZ;
    double total_time = (vals[0] + vals[1]) / hertz;
    double seconds = uptime - (vals[2] / hertz);
    float result;

    if (seconds <= 0)
        return 0.0;
    result = (float)((total_time / seconds) * 100);
    return result;
}

float get_process_cpu(const char *pid_str, top_t *top)
{
    char *path = get_stat_filepath(pid_str);
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    unsigned long vals[3] = {0, 0, 0};
    float res = 0.0;

    if (!path)
        return 0.0;
    file = fopen(path, "r");
    free(path);
    if (!file)
        return 0.0;
    if (getline(&line, &len, file) != -1) {
        parse_cpu_info(line, vals);
        res = calc_cpu_percent(vals, top->uptime);
    }
    free(line);
    fclose(file);
    return res;
}

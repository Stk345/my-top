/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** mem_percent.c
*/

#include "../include/my.h"

void open_meminfo(tasks_t *curr)
{
    FILE *file = fopen("/proc/meminfo", "r");
    char *buffer = NULL;
    size_t size = 0;

    if (file == NULL)
        return;
    while (getline(&buffer, &size, file) != -1) {
        if (strncmp(buffer, "MemTotal:", 9) == 0)
            sscanf(buffer, "MemTotal: %ld", &curr->total_mem);
    }
    free(buffer);
    fclose(file);
}

int calc_mem_percent(tasks_t *curr)
{
    open_meminfo(curr);
    if (curr->total_mem == 0)
        curr->mem_perc = 0.0f;
    else
        curr->mem_perc = ((double)curr->res /
            (double)curr->total_mem) * 100.0f;
    return 0;
}

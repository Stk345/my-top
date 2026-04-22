/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** load_average.c
*/

#include "../include/my.h"

int get_load_average(WINDOW *header)
{
    FILE *loadavg;
    float load1;
    float load2;
    float load3;

    loadavg = fopen("/proc/loadavg", "r");
    if (loadavg == NULL)
        return 84;
    fscanf(loadavg, "%f %f %f", &load1, &load2, &load3);
    fclose(loadavg);
    wprintw(header, "load average: %.2f, %.2f, %.2f", load1, load2, load3);
    return 0;
}

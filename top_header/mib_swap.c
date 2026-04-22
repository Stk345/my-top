/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** mib_swap.c
*/

#include "../include/my.h"

static void divide_swap(swap_t *swap, int divider)
{
    swap->total = swap->total / divider;
    swap->free = swap->free / divider;
    swap->used = swap->used / divider;
    swap->available = swap->available / divider;
}

void print_on_header_swap(WINDOW *header, swap_t *swap, top_t *top)
{
    int divider = 1;

    for (int i = 1; i < top->unit; i++)
        divider *= 1024;
    divide_swap(swap, divider);
    if (isinf(swap->total) || isnan(swap->total))
        swap->total = 0.0;
    if (isinf(swap->free) || isnan(swap->free))
        swap->free = 0.0;
    if (isinf(swap->used) || isnan(swap->used))
        swap->used = 0.0;
    if (isinf(swap->available) || isnan(swap->available))
        swap->available = 0.0;
    if (top->unit == 1)
        wprintw(header, "%i total, %i free, %i used. %i avail Mem",
            (int)swap->total, (int)swap->free, (int)swap->used,
            (int)swap->available);
    else
        wprintw(header, "%.1f total, %.1f free, %.1f used. %.1f avail Mem",
            swap->total, swap->free, swap->used, swap->available);
}

int get_swap_info(WINDOW *header, FILE *meminfo, top_t *top, swap_t *swap)
{
    char *buffer = NULL;
    size_t size = 0;

    while (getline(&buffer, &size, meminfo) != -1) {
        if (strncmp(buffer, "SwapTotal:", 10) == 0)
            sscanf(buffer, "SwapTotal: %lf", &swap->total);
        if (strncmp(buffer, "SwapFree:", 9) == 0)
            sscanf(buffer, "SwapFree: %lf", &swap->free);
        if (strncmp(buffer, "MemAvailable:", 13) == 0)
            sscanf(buffer, "MemAvailable: %lf", &swap->available);
    }
    swap->used = swap->total - swap->free;
    free(buffer);
    print_on_header_swap(header, swap, top);
    return 0;
}

int print_swap_mem(WINDOW *header, top_t *top)
{
    FILE *meminfo;
    swap_t swap = {0};
    char *unit = "KMGTPE";

    meminfo = fopen("/proc/meminfo", "r");
    if (meminfo == NULL)
        return 84;
    mvwprintw(header, 4, 0, "%ciB Swap : ", unit[top->unit - 1]);
    get_swap_info(header, meminfo, top, &swap);
    fclose(meminfo);
    return 0;
}

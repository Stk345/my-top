/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** mib_mem.c
*/

#include "../include/my.h"

static void divide_mem(mem_t *mem, int divider)
{
    mem->total = mem->total / divider;
    mem->free = mem->free / divider;
    mem->used = mem->used / divider;
    mem->buff = mem->buff / divider;
}

void print_on_header_mem(WINDOW *header, mem_t *mem, top_t *top)
{
    int divider = 1;

    for (int i = 1; i < top->unit; i++)
        divider *= 1024;
    divide_mem(mem, divider);
    if (isinf(mem->total) || isnan(mem->total))
        mem->total = 0.0;
    if (isinf(mem->free) || isnan(mem->free))
        mem->free = 0.0;
    if (isinf(mem->used) || isnan(mem->used))
        mem->used = 0.0;
    if (isinf(mem->buff) || isnan(mem->buff))
        mem->buff = 0.0;
    if (top->unit == 1)
        wprintw(header, "%i total, %i free, %i used, %i buff/cache",
            (int)mem->total, (int)mem->free, (int)mem->used, (int)mem->buff);
    else
        wprintw(header, "%.1f total, %.1f free, %.1f used, %.1f buff/cache",
            mem->total, mem->free, mem->used, mem->buff);
}

static void calc_mem_values(mem_t *mem)
{
    mem->buff = mem->buff + mem->cache;
    mem->used = mem->total - mem->available;
    mem->buff = mem->buff + mem->SReclaimable;
}

void mem_strncmp(char *buffer, mem_t *mem)
{
    if (strncmp(buffer, "MemTotal:", 9) == 0)
        sscanf(buffer, "MemTotal: %lf", &mem->total);
    if (strncmp(buffer, "MemFree:", 8) == 0)
        sscanf(buffer, "MemFree: %lf", &mem->free);
    if (strncmp(buffer, "Buffers:", 8) == 0)
        sscanf(buffer, "Buffers: %lf", &mem->buff);
    if (strncmp(buffer, "Cached:", 7) == 0)
        sscanf(buffer, "Cached: %lf", &mem->cache);
    if (strncmp(buffer, "SReclaimable:", 13) == 0)
        sscanf(buffer, "SReclaimable: %lf", &mem->SReclaimable);
    if (strncmp(buffer, "MemAvailable:", 13) == 0)
        sscanf(buffer, "MemAvailable: %lf", &mem->available);
}

int get_mem_info(WINDOW *header, top_t *top, FILE *meminfo, mem_t *mem)
{
    char *buffer = NULL;
    size_t size = 0;

    while (getline(&buffer, &size, meminfo) != -1)
        mem_strncmp(buffer, mem);
    calc_mem_values(mem);
    free(buffer);
    print_on_header_mem(header, mem, top);
    return 0;
}

int print_mib_mem(WINDOW *header, top_t *top)
{
    FILE *meminfo;
    mem_t mem = {0};
    char *unit = "KMGTPE";

    meminfo = fopen("/proc/meminfo", "r");
    if (meminfo == NULL)
        return 84;
    mvwprintw(header, 3, 0, "%ciB Mem : ", unit[top->unit - 1]);
    get_mem_info(header, top, meminfo, &mem);
    fclose(meminfo);
    return 0;
}

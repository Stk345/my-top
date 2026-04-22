/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** cpu_header.c
*/

#include "../include/my.h"

void print_cpu_usage(cpu_t *usage, WINDOW *header)
{
    wprintw(header, "%.1f us, %.1f sy, %.1f ni, %.1f id, %.1f wa, %.1f hi, "
        "%.1f si, %.1f st",
        (usage->user / usage->total) * 100,
        (usage->systeme / usage->total) * 100,
        (usage->nice / usage->total) * 100,
        (usage->idle / usage->total) * 100,
        (usage->iowait / usage->total) * 100,
        (usage->hardirq / usage->total) * 100,
        (usage->softirq / usage->total) * 100,
        (usage->steal / usage->total) * 100);
}

int calc_cpu(cpu_t *current, cpu_t *previous, WINDOW *header)
{
    cpu_t diff;

    diff.user = current->user - previous->user;
    diff.nice = current->nice - previous->nice;
    diff.systeme = current->systeme - previous->systeme;
    diff.idle = current->idle - previous->idle;
    diff.iowait = current->iowait - previous->iowait;
    diff.hardirq = current->hardirq - previous->hardirq;
    diff.softirq = current->softirq - previous->softirq;
    diff.steal = current->steal - previous->steal;
    diff.guest = current->guest - previous->guest;
    diff.guest_nice = current->guest_nice - previous->guest_nice;
    diff.total = diff.user + diff.nice + diff.systeme + diff.idle
        + diff.iowait + diff.hardirq + diff.softirq + diff.steal;
    if (diff.total > 0) {
        print_cpu_usage(&diff, header);
        return 0;
    }
    return 1;
}

void get_cpu_values(char *buffer, WINDOW *header, top_t *top)
{
    cpu_t cpu;

    sscanf(buffer, "cpu  %f %f %f %f %f %f %f %f %f %f", &cpu.user, &cpu.nice,
        &cpu.systeme, &cpu.idle, &cpu.iowait, &cpu.hardirq, &cpu.softirq,
        &cpu.steal, &cpu.guest, &cpu.guest_nice);
    cpu.total = cpu.user + cpu.nice + cpu.systeme + cpu.idle + cpu.iowait
        + cpu.hardirq + cpu.softirq + cpu.steal;
    if (top->current_iteration < 1)
        print_cpu_usage(&cpu, header);
    else
        calc_cpu(&cpu, &top->prev_cpu, header);
    top->prev_cpu = cpu;
    free(buffer);
}

int print_cpu_header(WINDOW *header, top_t *top)
{
    FILE *cpu_file;
    size_t size = 0;
    char *buffer;

    mvwprintw(header, 2, 0, "%%Cpu(s): ");
    cpu_file = fopen("/proc/stat", "r");
    if (cpu_file == NULL)
        return 84;
    if (getline(&buffer, &size, cpu_file) == -1) {
        fclose(cpu_file);
        return 84;
    }
    fclose(cpu_file);
    get_cpu_values(buffer, header, top);
    return 0;
}

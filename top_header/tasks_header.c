/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** tasks_header.c
*/

#include "../include/my.h"

void setup_total_tasks(total_tasks_t *total_tasks)
{
    total_tasks->Total = 0;
    total_tasks->R = 0;
    total_tasks->S = 0;
    total_tasks->T = 0;
    total_tasks->Z = 0;
}

void count_status(total_tasks_t *total_tasks, char status)
{
    if (status == 'R')
        total_tasks->R++;
    if (status == 'S')
        total_tasks->S++;
    if (status == 'T')
        total_tasks->T++;
    if (status == 'Z')
        total_tasks->Z++;
    total_tasks->Total++;
}

int get_tasks_status(top_t *top, WINDOW *header)
{
    total_tasks_t total_tasks_t;
    tasks_t *tmp;
    char status;

    setup_total_tasks(&total_tasks_t);
    while (top->tasks) {
        tmp = top->tasks;
        status = top->tasks->status;
        top->tasks = top->tasks->next;
        count_status(&total_tasks_t, status);
        free(tmp);
    }
    mvwprintw(header, 1, 0, "Tasks: %d total, %d running, %d sleeping,"
        " %d stopped, %d zombie", total_tasks_t.Total, total_tasks_t.R,
        total_tasks_t.S, total_tasks_t.T, total_tasks_t.Z);
    return 0;
}

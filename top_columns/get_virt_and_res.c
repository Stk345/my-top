/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** get_virt_and_res.c
*/

#include "../include/my.h"

static void get_values(FILE *file, tasks_t *curr)
{
    char *buffer = NULL;
    size_t size = 0;

    curr->virt = 0;
    curr->res = 0;
    while (getline(&buffer, &size, file) != -1) {
        if (strncmp(buffer, "VmSize:", 7) == 0)
            sscanf(buffer, "VmSize: %ld", &curr->virt);
        if (strncmp(buffer, "VmRSS:", 6) == 0)
            sscanf(buffer, "VmRSS: %ld", &curr->res);
        if (strncmp(buffer, "RssFile:", 8) == 0)
            sscanf(buffer, "RssFile: %ld", &curr->file);
        if (strncmp(buffer, "RssShmem:", 9) == 0)
            sscanf(buffer, "RssShmem: %ld", &curr->shmem);
    }
    curr->shr = curr->file + curr->shmem;
    free(buffer);
}

static void init_values(tasks_t *curr)
{
    curr->virt = 0;
    curr->res = 0;
    curr->file = 0;
    curr->shmem = 0;
    curr->shr = 0;
    curr->total_mem = 0;
    curr->mem_perc = 0.0f;
}

int get_virt_and_res(const char *pid_str, tasks_t *curr)
{
    char *path = get_status_filepath(pid_str);
    FILE *file = NULL;
    char *buffer = NULL;
    size_t size = 0;

    if (path == NULL)
        return 84;
    file = fopen(path, "r");
    free(path);
    init_values(curr);
    if (file == NULL)
        return 84;
    get_values(file, curr);
    calc_mem_percent(curr);
    fclose(file);
    return 0;
}

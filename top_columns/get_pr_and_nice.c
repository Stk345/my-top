/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** get_pr_and_nice.c
*/

#include "../include/my.h"

int search_pr_nice(char *buffer, int *pr, int *nice)
{
    char *value;
    int i = 2;
    char *start = strrchr(buffer, ')');

    if (start == NULL)
        return 84;
    start++;
    value = strtok(start, " ");
    while (value != NULL) {
        i++;
        if (i == 18)
            *pr = atoi(value);
        if (i == 19)
            *nice = atoi(value);
        value = strtok(NULL, " ");
    }
    return 0;
}

int get_pr_and_nice(const char *pid_str, int *pr, int *nice)
{
    char *path = get_stat_filepath(pid_str);
    FILE *file = NULL;
    char *buffer;
    size_t size = 0;

    *pr = 0;
    *nice = 0;
    if (path == NULL)
        return 84;
    file = fopen(path, "r");
    free(path);
    if (file == NULL)
        return 84;
    getline(&buffer, &size, file);
    fclose(file);
    if (buffer == NULL)
        return 84;
    search_pr_nice(buffer, pr, nice);
    free(buffer);
    return 0;
}

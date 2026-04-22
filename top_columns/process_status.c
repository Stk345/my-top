/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** process_status.c
*/

#include "../include/my.h"

static char parse_state_line(char *line)
{
    int i = 6;

    if (strncmp(line, "State:", 6) != 0)
        return 84;
    while (line[i] && (line[i] == '\t' || line[i] == ' '))
        i++;
    return line[i];
}

static char get_state_from_file(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    char state = 0;

    while (getline(&line, &len, file) != -1) {
        state = parse_state_line(line);
        if (state != 84)
            break;
    }
    free(line);
    return state;
}

char get_process_status(const char *pid_str)
{
    char *path = get_status_filepath((char *)pid_str);
    FILE *file = NULL;
    char state = ' ';

    if (path == NULL)
        return ' ';
    file = fopen(path, "r");
    free(path);
    if (file == NULL)
        return ' ';
    state = get_state_from_file(file);
    fclose(file);
    return state;
}

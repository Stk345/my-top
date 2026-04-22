/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** header_user.c
*/

#include "../include/my.h"

int is_number_string(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int get_user_nb(WINDOW *header)
{
    struct dirent *entry;
    int user_count = 0;
    DIR *sessions_dir = opendir("/run/systemd/sessions/");

    if (sessions_dir == NULL)
        return 84;
    entry = readdir(sessions_dir);
    while (entry != NULL) {
        if (is_number_string(entry->d_name))
            user_count++;
        entry = readdir(sessions_dir);
    }
    closedir(sessions_dir);
    if (user_count > 1)
        wprintw(header, ", %d users, ", user_count);
    else
        wprintw(header, ", %d user, ", user_count);
    return 0;
}

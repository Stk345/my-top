/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** user.c
*/

#include "../include/my.h"

static char *format_user_name(char *name)
{
    char *new = NULL;
    int len = my_strlen(name);

    if (len > 7) {
        new = malloc(sizeof(char) * 9);
        if (new == NULL)
            return NULL;
        my_strncpy(new, name, 7);
        new[7] = '+';
        new[8] = '\0';
    } else {
        new = malloc(sizeof(char) * (len + 1));
        if (new == NULL)
            return NULL;
        my_strncpy(new, name, len);
        new[len] = '\0';
    }
    free(name);
    return new;
}

int get_uid_from_line(char *line)
{
    int i = 4;

    if (strncmp(line, "Uid:", 4) != 0)
        return -1;
    while (line[i] && (line[i] == '\t' || line[i] == ' '))
        i++;
    return atoi(&line[i]);
}

static int get_proc_uid(const char *pid_str)
{
    char *path = get_status_filepath((char *)pid_str);
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    int uid = -1;

    free(path);
    if (!file)
        return -1;
    while (getline(&line, &len, file) != -1) {
        uid = get_uid_from_line(line);
        if (uid != -1)
            break;
    }
    free(line);
    fclose(file);
    return uid;
}

static char *parse_passwd_line(char *line, int target_uid)
{
    int i = 0;
    int col = 0;
    int n_len = 0;
    char *name = NULL;

    while (line[n_len] && line[n_len] != ':')
        n_len++;
    while (line[i] && col < 2) {
        if (line[i] == ':')
            col++;
        i++;
    }
    if (col == 2 && atoi(&line[i]) == target_uid) {
        name = malloc(sizeof(char) * (n_len + 1));
        if (name) {
            my_strncpy(name, line, n_len);
            name[n_len] = '\0';
        }
    }
    return name;
}

static char *get_name_from_uid(int uid)
{
    FILE *file = fopen("/etc/passwd", "r");
    char *line = NULL;
    size_t len = 0;
    char *name = NULL;

    if (!file)
        return NULL;
    while (getline(&line, &len, file) != -1) {
        name = parse_passwd_line(line, uid);
        if (name != NULL) {
            free(line);
            fclose(file);
            return format_user_name(name);
        }
    }
    free(line);
    fclose(file);
    return NULL;
}

char *get_user(const char *pid_str)
{
    int uid = get_proc_uid(pid_str);

    if (uid == -1)
        return NULL;
    return get_name_from_uid(uid);
}

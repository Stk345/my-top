/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** time.c
*/

#include "../include/my.h"

int get_hour(WINDOW *header, char *time_str)
{
    int hour;
    int minute;
    int second;

    if (time_str == NULL)
        return 84;
    hour = ((time_str[11] - '0') * 10 + (time_str[12] - '0') + 1) % 24;
    minute = (time_str[14] - '0') * 10 + (time_str[15] - '0');
    second = (time_str[17] - '0') * 10 + (time_str[18] - '0');
    mvwprintw(header, 0, 0, "top - %02d:%02d:%02d ", hour, minute, second);
    free(time_str);
    return 0;
}

int hour(WINDOW *header)
{
    FILE *time;
    char *buffer = NULL;
    size_t size = 0;

    time = fopen("/proc/driver/rtc", "r");
    if (time == NULL)
        return 84;
    if (getline(&buffer, &size, time) == -1) {
        free(buffer);
        fclose(time);
        return 84;
    }
    fclose(time);
    get_hour(header, buffer);
    return 0;
}

int get_nbr_len(long n)
{
    int len = (n <= 0) ? 1 : 0;
    long tmp = (n < 0) ? -n : n;

    while (tmp > 0) {
        tmp /= 10;
        len++;
    }
    return len;
}

static char *int_to_str(int num)
{
    long n = num;
    int len = get_nbr_len(n);
    char *res = malloc(len + 1);

    if (!res)
        return NULL;
    res[len] = '\0';
    if (n <= 0)
        res[0] = (n == 0) ? '0' : '-';
    if (n < 0)
        n = -n;
    while (n > 0) {
        len--;
        res[len] = (n % 10) + '0';
        n /= 10;
    }
    return res;
}

static void append_time_part(char *str, int val, char *sep)
{
    char *tmp;

    if (sep)
        strcat(str, sep);
    if (val < 10)
        strcat(str, "0");
    tmp = int_to_str(val);
    if (tmp) {
        strcat(str, tmp);
        free(tmp);
    }
}

static char *format_time(unsigned long ticks)
{
    char *str = malloc(16);
    char *tmp;
    unsigned long tot = (ticks * 100) / HZ;
    int s = (tot / 100) % 60;
    int m = (tot / 100) / 60;
    int c = tot % 100;

    if (!str)
        return NULL;
    str[0] = '\0';
    tmp = int_to_str(m);
    if (tmp) {
        strcat(str, tmp);
        free(tmp);
    }
    append_time_part(str, s, ":");
    append_time_part(str, c, ".");
    return str;
}

static unsigned long parse_ticks(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    char *tok;
    int i = 1;
    unsigned long t = 0;

    if (getline(&line, &len, file) == -1) {
        free(line);
        return 0;
    }
    tok = strtok(line, " ");
    while (tok && i <= 15) {
        if (i == 14 || i == 15)
            t += atoi(tok);
        tok = strtok(NULL, " ");
        i++;
    }
    free(line);
    return t;
}

char *get_process_time(top_t *top, char *pid_str)
{
    char *path = get_stat_filepath(pid_str);
    FILE *file;
    unsigned long t;

    if (!path)
        return NULL;
    file = fopen(path, "r");
    free(path);
    if (!file)
        return NULL;
    t = parse_ticks(file);
    fclose(file);
    return format_time(t);
}

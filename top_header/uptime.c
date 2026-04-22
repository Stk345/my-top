/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** uptime.c
*/

#include "../include/my.h"

void print_hours_minutes(float uptime, WINDOW *header)
{
    int hours;
    int minutes;

    hours = (int)(uptime / 3600);
    if (hours < 10)
        wprintw(header, "0");
    wprintw(header, "%d:", hours);
    uptime -= hours * 3600;
    minutes = (int)(uptime / 60);
    if (minutes < 10)
        wprintw(header, "0");
    wprintw(header, "%d", minutes);
}

static float print_days(float uptime, WINDOW *header)
{
    int days;

    if (uptime >= 86400) {
        days = (int)(uptime / 86400);
        if (days > 1)
            wprintw(header, "%d days, ", days);
        else
            wprintw(header, "%d day, ", days);
        uptime -= days * 86400;
    }
    return uptime;
}

static void print_uptime(float uptime, WINDOW *header)
{
    int minutes;

    wprintw(header, "up ");
    uptime = print_days(uptime, header);
    if (uptime >= 3600) {
        print_hours_minutes(uptime, header);
        uptime -= ((int)(uptime / 3600)) * 3600;
        return;
    }
    minutes = (int)(uptime / 60);
    if (minutes > 1)
        wprintw(header, "%d mins", minutes);
    else
        wprintw(header, "%d min", minutes);
}

int clean_uptime(char *buffer, WINDOW *header)
{
    int len = 0;
    char *uptime_str;
    float uptime;

    if (buffer == NULL)
        return 84;
    while (buffer[len] != ' ' && buffer[len] != '\0')
        len++;
    uptime_str = malloc(sizeof(char) * (len + 1));
    if (uptime_str == NULL) {
        free(buffer);
        return 84;
    }
    my_strncpy(uptime_str, buffer, len);
    uptime_str[len] = '\0';
    uptime = atof(uptime_str);
    free(uptime_str);
    free(buffer);
    print_uptime(uptime, header);
    return uptime;
}

int get_uptime(WINDOW *header)
{
    FILE *uptime;
    char *buffer = NULL;
    size_t size = 0;
    int uptime_value;

    uptime = fopen("/proc/uptime", "r");
    if (uptime == NULL)
        return 84;
    if (getline(&buffer, &size, uptime) == -1) {
        free(buffer);
        fclose(uptime);
        return 84;
    }
    fclose(uptime);
    uptime_value = clean_uptime(buffer, header);
    if (uptime_value == 84)
        return 84;
    return uptime_value;
}

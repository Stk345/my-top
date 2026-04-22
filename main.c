/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mysudo-6
** File description:
** main.c
*/

#include "include/my.h"

int check_errors(int argc, char **argv, int i)
{
    if (argv[i][0] != '-') {
        write(2, "Invalid argument\n", 17);
        return 84;
    }
    if (argc > i + 1 && (strcmp(argv[i], "-d") == 0 ||
            strcmp(argv[i], "-n") == 0)) {
        if (argc < 3) {
            write(2, "Missing argument\n", 18);
            return 84;
        }
        if (argc > i + 1 && atof(argv[i + 1]) <= 0) {
            write(2, "Invalid value\n", 14);
            return 84;
        }
    } else {
        write(2, "Invalid argument\n", 17);
        return 84;
    }
    return 0;
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i += 2) {
        if (check_errors(argc, argv, i) == 84)
            return 84;
    }
    return start(argc, argv);
}

/*
** EPITECH PROJECT, 2025
** my putstr
** File description:
** display one by one character of a string
*/

#include "../../include/my.h"

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        my_putchar(str[i]);
        i++;
    }
    return (my_strlen(str));
}

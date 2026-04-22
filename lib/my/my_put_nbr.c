/*
** EPITECH PROJECT, 2025
** my_put_nbr
** File description:
** print the nomber in parameter
*/
#include "../../include/my.h"

int my_put_nbr(int nb)
{
    int length = 1;

    if (nb == -2147483648) {
        my_putstr("-2147483648");
        return 11;
    }
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
        length++;
    }
    if (nb >= 10) {
        length += my_put_nbr(nb / 10);
    }
    my_putchar((nb % 10) + '0');
    return length;
}

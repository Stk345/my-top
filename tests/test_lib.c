/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** test_lib.c
*/

#include "../include/my.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(lib, my_put_nbr, .init = cr_redirect_stdout)
{
    my_put_nbr(42);
    my_put_nbr(-12);
    cr_assert_stdout_eq_str("42-12");
}

Test(lib, my_strlen)
{
    cr_assert_eq(my_strlen(""), 0);
    cr_assert_eq(my_strlen("Hello"), 5);
    cr_assert_eq(my_strlen("This is a test"), 14);
    cr_assert_eq(my_strlen("1234567890"), 10);
}

Test(lib, my_strncpy)
{
    char dest[20];

    my_strncpy(dest, "Hello, World!", 5);
    dest[5] = '\0';
    cr_assert_str_eq(dest, "Hello");
    my_strncpy(dest, "This is a test", 14);
    dest[14] = '\0';
    cr_assert_str_eq(dest, "This is a test");
    my_strncpy(dest, "1234567890", 10);
    dest[10] = '\0';
    cr_assert_str_eq(dest, "1234567890");
    my_strncpy(dest, "Short", 10);
    dest[10] = '\0';
    cr_assert_str_eq(dest, "Short");
}

Test(lib, my_putstr, .init = cr_redirect_stdout)
{
    my_putstr("Hello World");
    cr_assert_stdout_eq_str("Hello World");
}

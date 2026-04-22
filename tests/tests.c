/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** tests.c
*/

#include "../include/my.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(my_top, test_my_top_exit)
{
    char *argv[] = {"./mytop", NULL};
    int ret = 1;
    FILE *file = fopen("tests/input.txt", "w+");

    fprintf(file, "q");
    fclose(file);
    freopen("tests/input.txt", "r", stdin);
    cr_redirect_stdout();

    ret = start(1, argv);
    cr_assert_eq(ret, 0);
    remove("tests/input.txt");
}

Test(my_top, test_my_top_shift_e)
{
    char *argv[] = {"./mytop", NULL};
    int ret = 1;
    FILE *file = fopen("tests/input.txt", "w+");

    fprintf(file, "E");
    fprintf(file, "q");
    fclose(file);
    freopen("tests/input.txt", "r", stdin);
    cr_redirect_stdout();

    ret = start(1, argv);
    cr_assert_eq(ret, 0);
    remove("tests/input.txt");
}

Test(my_top, test_my_top_kill)
{
    char *argv[] = {"./mytop", NULL};
    int ret = 1;
    FILE *file = fopen("tests/input.txt", "w+");

    fprintf(file, "k");
    fprintf(file, "0");
    fprintf(file, "\r");
    fprintf(file, "q");
    fclose(file);
    freopen("tests/input.txt", "r", stdin);
    cr_redirect_stdout();

    ret = start(1, argv);
    cr_assert_eq(ret, 0);
    remove("tests/input.txt");
}

Test(my_top, test_my_top_n)
{
    char *argv[] = {"./mytop", "-n", "1", NULL};
    int ret = 1;

    cr_redirect_stdout();
    ret = start(3, argv);
    cr_assert_eq(ret, 0);
}

Test(change_unit, test_change_unit_kill_switch)
{
    top_t top = {0};

    top.unit = 6;
    change_unit(&top, 'E');
    cr_assert_eq(top.unit, 1);
}

Test(start, n_iterations_limit)
{
    char *argv[] = {"./mytop", "-n", "1", NULL};
    int ret = 1;

    cr_redirect_stdout();
    ret = start(3, argv);
    cr_assert_eq(ret, 0);
}

Test(my_top, test_kill_process_flow)
{
    int ret;
    char *argv[] = {"./mytop", NULL};
    FILE *file = fopen("tests/input_kill.txt", "w+");

    fprintf(file, "k");
    fprintf(file, "0\n");
    fprintf(file, "q");
    fclose(file);
    freopen("tests/input_kill.txt", "r", stdin);
    cr_redirect_stdout();
    cr_redirect_stderr();
    ret = start(1, argv);
    cr_assert_eq(ret, 0);
    remove("tests/input_kill.txt");
}

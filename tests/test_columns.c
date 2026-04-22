/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** test.c
*/


#include "../include/my.h"
#include <criterion/criterion.h>

Test(get_nbr_len, test_get_nbr_len)
{
    cr_assert_eq(get_nbr_len(0), 1);
    cr_assert_eq(get_nbr_len(10), 2);
    cr_assert_eq(get_nbr_len(100), 3);
    cr_assert_eq(get_nbr_len(-42), 3);
}

Test(search_pr_nice, test_search_pr_nice)
{
    char buffer[] = "12345 (task) S 4 5 6 7 8 9 10 11 "
        "12 13 14 15 16 17 18 19 20 21 22";
    int pr = 0;
    int nice = 0;
    int ret;

    ret = search_pr_nice(buffer, &pr, &nice);
    cr_assert_eq(pr, 18);
    cr_assert_eq(nice, 19);
    cr_assert_eq(ret, 0);
}

Test(search_pr_nice, test_search_pr_nice_fail)
{
    char buffer[] = "invalid buffer";
    int pr = 0;
    int nice = 0;
    int ret;

    ret = search_pr_nice(buffer, &pr, &nice);
    cr_assert_eq(ret, 84);
}

Test(get_hour, test_null_hour)
{
    WINDOW *header = initscr();
    char *time_str = NULL;

    int ret = get_hour(header, time_str);
    cr_assert_eq(ret, 84);
    endwin();
}

Test(parse_cpu_info, test_parse_cpu_info)
{
    char line[] = "12345 (task) S 4 5 6 7 8 9 10 "
        "11 12 13 14 15 16 17 18 19 20 21 22";
    unsigned long vals[3] = {0, 0, 0};

    parse_cpu_info(line, vals);
    cr_assert_eq(vals[0], 14);
    cr_assert_eq(vals[1], 15);
    cr_assert_eq(vals[2], 22);
}

Test(get_uid_from_line, test_valid_uid_line)
{
    char line[] = "Uid:\t1000\t1000\t1000\t1000";
    int uid = get_uid_from_line(line);
    cr_assert_eq(uid, 1000);
}

Test(get_uid_from_line, test_invalid_uid_line)
{
    char line[] = "Invalid line";
    int uid = get_uid_from_line(line);
    cr_assert_eq(uid, -1);
}

Test(get_uid_from_line, test_space)
{
    char line[] = "Uid: 1000\t1000 1000 1000";
    int uid = get_uid_from_line(line);
    cr_assert_eq(uid, 1000);
}

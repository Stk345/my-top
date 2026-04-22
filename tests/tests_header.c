/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** tests_header.c
*/

#include "../include/my.h"
#include <criterion/criterion.h>

Test(memory, test_mem_parsing)
{
    mem_t mem = {0};

    mem_strncmp("MemTotal:       16384 kB", &mem);
    mem_strncmp("MemFree:         1024 kB", &mem);
    mem_strncmp("MemAvailable:    8000 kB", &mem);
    cr_assert_float_eq(mem.total, 16384.0, 0.001);
    cr_assert_float_eq(mem.free, 1024.0, 0.001);
    cr_assert_float_eq(mem.available, 8000.0, 0.001);
}

Test(print_on_header_mem, test_inf_mem)
{
    mem_t mem = {INFINITY, INFINITY, INFINITY,
        INFINITY, INFINITY, INFINITY, INFINITY};
    top_t top = {0};
    WINDOW *header = initscr();

    top.unit = 2;
    print_on_header_mem(header, &mem, &top);
    cr_assert_eq(mem.total, 0.0);
    cr_assert_eq(mem.free, 0.0);
    cr_assert_eq(mem.used, 0.0);
    cr_assert_eq(mem.buff, 0.0);
    endwin();
}

Test(print_on_header_swap, test_inf_swap)
{
    swap_t swap = {INFINITY, INFINITY, INFINITY, INFINITY};
    top_t top = {0};
    WINDOW *header = initscr();

    top.unit = 2;
    print_on_header_swap(header, &swap, &top);
    cr_assert_eq(swap.total, 0.0);
    cr_assert_eq(swap.free, 0.0);
    cr_assert_eq(swap.used, 0.0);
    cr_assert_eq(swap.available, 0.0);
    endwin();
}

Test(print_on_header_mem, test_nan_mem)
{
    mem_t mem = {NAN, NAN, NAN, NAN, NAN, NAN, NAN};
    top_t top = {0};
    WINDOW *header = initscr();

    top.unit = 2;
    print_on_header_mem(header, &mem, &top);
    cr_assert_eq(mem.total, 0.0);
    cr_assert_eq(mem.free, 0.0);
    cr_assert_eq(mem.used, 0.0);
    cr_assert_eq(mem.buff, 0.0);
    endwin();
}

Test(print_on_header_swap, test_nan_swap)
{
    swap_t swap = {NAN, NAN, NAN, NAN};
    top_t top = {0};
    WINDOW *header = initscr();

    top.unit = 2;
    print_on_header_swap(header, &swap, &top);
    cr_assert_eq(swap.total, 0.0);
    cr_assert_eq(swap.free, 0.0);
    cr_assert_eq(swap.used, 0.0);
    cr_assert_eq(swap.available, 0.0);
    endwin();
}

Test(calc_cpu, test_calc_cpu)
{
    cpu_t current = {200.0, 50.0, 100.0, 500.0, 20.0,
        10.0, 5.0, 0.0, 0.0, 0.0, 885.0};
    cpu_t previous = {100.0, 25.0, 50.0, 400.0, 10.0,
        5.0, 2.5, 0.0, 0.0, 0.0, 592.5};
    WINDOW *header = initscr();
    int ret;

    ret = calc_cpu(&current, &previous, header);
    endwin();
    cr_assert_eq(ret, 0);
}

Test(calc_cpu, test_calc_cpu_no_change)
{
    cpu_t current = {100.0, 25.0, 50.0, 400.0, 10.0,
        5.0, 2.5, 0.0, 0.0, 0.0, 592.5};
    cpu_t previous = {100.0, 25.0, 50.0, 400.0, 10.0,
        5.0, 2.5, 0.0, 0.0, 0.0, 592.5};
    WINDOW *header = initscr();
    int ret;

    ret = calc_cpu(&current, &previous, header);
    endwin();
    cr_assert_eq(ret, 1);
}

Test(clean_uptime, test_incorrect_buffer)
{
    WINDOW *header = initscr();
    char *buffer = NULL;
    int ret;

    ret = clean_uptime(buffer, header);
    endwin();
    cr_assert_eq(ret, 84);
}

Test(is_number_string, test_is_number_string)
{
    cr_assert_eq(is_number_string("12345"), 1);
    cr_assert_eq(is_number_string("12a45"), 0);
}

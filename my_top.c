/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** my_top.c
*/

#include "include/my.h"

void display_functions(WINDOW *header, WINDOW *tasks, top_t *top)
{
    clear();
    hour(header);
    top->uptime = get_uptime(header);
    get_user_nb(header);
    get_load_average(header);
    print_mib_mem(header, top);
    print_swap_mem(header, top);
    print_cpu_header(header, top);
    print_tasks(tasks, top);
    top->first_pid = top->tasks->pid;
    get_tasks_status(top, header);
    refresh();
}

static int kill_process(top_t *top, int first_pid)
{
    int pid = 0;

    nodelay(stdscr, FALSE);
    echo();
    while (top->kill_switch) {
        wattr_on(top->header, A_BOLD, NULL);
        mvwprintw(top->header, 5, 0, "PID to signal/kill [default pid = %d] ",
            first_pid);
        wattr_off(top->header, A_BOLD, NULL);
        wrefresh(top->header);
        wscanw(top->header, "%d", &pid);
        if (pid > 0)
            kill(pid, SIGKILL);
        top->kill_switch = 0;
        refresh();
    }
    noecho();
    nodelay(stdscr, TRUE);
    return 0;
}

void change_unit(top_t *top, double input)
{
    if (input == ('E')) {
        top->unit++;
        if (top->unit > 6)
            top->unit = 1;
    }
    if (input == ('k')) {
        top->kill_switch = 1;
        kill_process(top, top->first_pid);
    }
    return;
}

int my_top(int argc, char **argv, top_t *top)
{
    double input;

    noecho();
    nodelay(stdscr, TRUE);
    while (top->limit_process == 0 ||
        top->current_iteration < top->limit_process) {
        timeout(top->refresh_rate * 1000);
        display_functions(top->header, top->tasks_win, top);
        input = getch();
        if (input == 'q')
            break;
        change_unit(top, input);
        top->current_iteration++;
    }
    free_tasks(top);
    free(top);
    endwin();
    return 0;
}

int setup_top(int argc, char **argv, top_t *top)
{
    top->refresh_rate = 3.0;
    top->limit_process = 0;
    top->nb_process = 1;
    top->unit = 2;
    top->kill_switch = 0;
    top->first_pid = 0;
    top->tasks = NULL;
    top->current_iteration = 0;;
    return 0;
}

int start(int argc, char **argv)
{
    top_t *top = malloc(sizeof(top_t));

    if (top == NULL)
        return 84;
    initscr();
    setup_top(argc, argv, top);
    top->tasks_win = subwin(stdscr, LINES - 6, COLS, 6, 0);
    top->header = subwin(stdscr, 6, COLS, 0, 0);
    if (top->tasks_win == NULL || top->header == NULL) {
        free(top);
        endwin();
        return 84;
    }
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 && i + 1 < argc)
            top->refresh_rate = atof(argv[i + 1]);
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc)
            top->limit_process = atoi(argv[i + 1]);
    }
    return my_top(argc, argv, top);
}

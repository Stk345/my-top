/*
** EPITECH PROJECT, 2025
** my header
** File description:
** header for all my func
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include "struct.h"
#include "stdio.h"
#include <dirent.h>
#include <math.h>
#include <signal.h>

#ifndef MY_H_
    #define MY_H_

    #define HZ 100

void my_putchar(char c);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_put_nbr(int nb);
int my_top(int argc, char **argv, top_t *top);
char *my_strncpy(char *dest, char const *src, int n);
int get_uptime(WINDOW *header);
int print_tasks(WINDOW *win, top_t *top);
int hour(WINDOW *header);
int print_cpu_header(WINDOW *header, top_t *top);
char *time_process(const char *pid_str, top_t *top);
char get_process_status(const char *pid_str);
int print_mib_mem(WINDOW *header, top_t *top);
int print_swap_mem(WINDOW *header, top_t *top);
char *get_user(const char *pid_str);
int get_load_average(WINDOW *header);
int get_user_nb(WINDOW *header);
int get_tasks_status(top_t *top, WINDOW *header);
int get_pr_and_nice(const char *pid_str, int *pr, int *nice);
char *get_process_time(top_t *top, char *pid_str);
int get_virt_and_res(const char *pid_str, tasks_t *curr);
char *get_status_filepath(const char *pid_str);
char *get_stat_filepath(const char *pid_str);
int get_nbr_len(long n);
void mem_strncmp(char *buffer, mem_t *mem);
int search_pr_nice(char *buffer, int *pr, int *nice);
int start(int argc, char **argv);
float get_process_cpu(const char *pid_str, top_t *top);
void print_hours_minutes(float uptime, WINDOW *header);
void print_on_header_mem(WINDOW *header, mem_t *mem, top_t *top);
void print_on_header_swap(WINDOW *header, swap_t *swap, top_t *top);
int get_hour(WINDOW *header, char *time_str);
void parse_cpu_info(char *line, unsigned long *vals);
int calc_cpu(cpu_t *current, cpu_t *previous, WINDOW *header);
int clean_uptime(char *buffer, WINDOW *header);
int is_number_string(char *str);
void change_unit(top_t *top, double input);
void free_tasks(top_t *top);
int calc_mem_percent(tasks_t *curr);
int get_uid_from_line(char *line);

#endif /* MY_H_ */

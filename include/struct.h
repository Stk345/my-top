/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** struct.h
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct tasks_s {
    int pid;
    char *user;
    float cpu;
    float mem;
    char *time;
    char status;
    char command[256];
    int pr;
    int nice;
    long virt;
    long res;
    long anon;
    long file;
    long shmem;
    long shr;
    long total_mem;
    float mem_perc;
    struct tasks_s *next;
} tasks_t;

typedef struct cpu_s {
    float user;
    float nice;
    float systeme;
    float idle;
    float iowait;
    float hardirq;
    float softirq;
    float steal;
    float guest;
    float guest_nice;
    float total;
} cpu_t;

typedef struct top_s {
    float refresh_rate;
    int uptime;
    int nb_process;
    int limit_process;
    int unit;
    int kill_switch;
    double first_pid;
    int current_iteration;
    cpu_t prev_cpu;
    tasks_t *tasks;
    WINDOW *header;
    WINDOW *tasks_win;
} top_t;

typedef struct mem_s {
    double total;
    double free;
    double used;
    double buff;
    double cache;
    double SReclaimable;
    double available;
} mem_t;

typedef struct swap_s {
    double total;
    double free;
    double used;
    double available;
} swap_t;

typedef struct total_tasks_s {
    int Total;
    int R;
    int S;
    int T;
    int Z;
} total_tasks_t;

#endif /* STRUCT_H_ */

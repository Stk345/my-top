/*
** EPITECH PROJECT, 2025
** G-PSU-100-NAN-1-1-mytop-3
** File description:
** tasks.c
*/

#include "../include/my.h"

char *get_status_filepath(const char *pid_str)
{
    int len = my_strlen("/proc/") + my_strlen(pid_str) + 8;
    char *path = malloc(sizeof(char) * (len + 1));

    if (path == NULL)
        return NULL;
    path[0] = '\0';
    strcat(path, "/proc/");
    strcat(path, pid_str);
    strcat(path, "/status");
    return path;
}

char *get_stat_filepath(const char *pid_str)
{
    int len = strlen("/proc/") + strlen(pid_str) + 8;
    char *path = malloc(sizeof(char) * (len + 1));

    if (path == NULL)
        return NULL;
    path[0] = '\0';
    strcat(path, "/proc/");
    strcat(path, pid_str);
    strcat(path, "/stat");
    return path;
}

void free_tasks(top_t *top)
{
    tasks_t *tmp;

    while (top->tasks) {
        tmp = top->tasks;
        top->tasks = top->tasks->next;
        free(tmp->user);
        free(tmp->time);
        free(tmp);
    }
    top->nb_process = 0;
}

static void get_proc_name(tasks_t *task, const char *pid_str)
{
    char path[256];
    int fd;
    int len;

    snprintf(path, sizeof(path), "/proc/%s/comm", pid_str);
    fd = open(path, O_RDONLY);
    if (fd != -1) {
        len = read(fd, task->command, sizeof(task->command) - 1);
        if (len > 0)
            task->command[len - 1] = '\0';
        close(fd);
    } else {
        snprintf(task->command, sizeof(task->command), "Unknown");
    }
}

static int add_task_to_list(top_t *top, const char *pid_str)
{
    tasks_t *new_task = malloc(sizeof(tasks_t));

    if (new_task == NULL)
        return 84;
    new_task->pid = atoi(pid_str);
    get_proc_name(new_task, pid_str);
    new_task->cpu = get_process_cpu(pid_str, top);
    new_task->mem = 0.0;
    new_task->status = get_process_status(pid_str);
    new_task->time = get_process_time(top, (char *)pid_str);
    new_task->user = get_user(pid_str);
    new_task->next = top->tasks;
    top->tasks = new_task;
    top->nb_process += 1;
    get_pr_and_nice(pid_str, &new_task->pr, &new_task->nice);
    get_virt_and_res(pid_str, new_task);
    return 0;
}

int check_tasks(top_t *top)
{
    struct dirent *entry;
    DIR *dir = opendir("/proc");

    if (dir == NULL)
        return 84;
    free_tasks(top);
    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_name[0] >= '0' && entry->d_name[0] <= '9') {
            add_task_to_list(top, entry->d_name);
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return 0;
}

int print_tasks(WINDOW *win, top_t *top)
{
    tasks_t *curr;
    int row = 1;
    int largeur = getmaxx(win);
    const char *header = "  PID USER      PR  NI        VIRT        RES        "
        "SHR S  %CPU  %MEM     TIME+ COMMAND";

    wattron(win, A_REVERSE);
    mvwprintw(win, 0, 0, "%-*s", largeur, header);
    wattroff(win, A_REVERSE);
    check_tasks(top);
    curr = top->tasks;
    while (curr != NULL && row < LINES - 5) {
        mvwprintw(win, row, 0, "%5d %-8s %3d %3d %11ld %10ld %10ld "
            "%1c %5.1f %5.1f %9s %-16s", curr->pid, curr->user, curr->pr,
            curr->nice, curr->virt, curr->res, curr->shr,
            curr->status, curr->cpu, curr->mem_perc, curr->time, curr->command);
        curr = curr->next;
        row++;
    }
    return 0;
}

/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** shell_loop
*/

#include "mysh.h"
#include "get_next_line.h"

void check_binary(char **str, char **envp)
{
    if (execve(str[0], str, envp) == -1) {
        write(2, str[0], my_strlen(str[0]));
        write(2, ": Command not found.\n", 21);
        exit(1);
    }
}

void error_signal(int id, int status)
{
    do {
        id = waitpid(id, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == 11 && WCOREDUMP(status))
            write(2, "Segmentation fault (core dumped)\n", 33);
        if (WTERMSIG(status) == 11 && !WCOREDUMP(status))
            write(2, "Segmentation fault\n", 19);
        if (WTERMSIG(status) == 8 && WCOREDUMP(status))
            write(2, "Floating exception (core dumped)\n", 33);
        if (WTERMSIG(status) == 8 && !WCOREDUMP(status))
            write(2, "Floating exception\n", 19);
    }
}

void command_parsor(controll_t *s_controll)
{
    int id = -300, status = 1;
    s_controll->command = 0;
    if (s_controll->str[0] == NULL) return;
    if (my_strcmp(s_controll->str[0], "setenv") == 0) my_setenv(s_controll);
    if (my_strcmp(s_controll->str[0], "unsetenv") == 0)
        my_unsetenv(s_controll);
    if (my_strcmp(s_controll->str[0], "cd") == 0) my_cd(s_controll);
    if (my_strcmp(s_controll->str[0], "env") == 0)
        check_env(s_controll->envp, s_controll);
    if (s_controll->str[0] != NULL && check_if_path(s_controll->str)) {
        s_controll->command = 1;
        id = fork();
        if (id == 0) check_binary(s_controll->str, s_controll->envp);
    }
    if (s_controll->command == 0 && s_controll->str[0] != NULL) {
        path_handling(s_controll);
    }
    error_signal(id, status);
}

void shell_loop(controll_t *s_controll)
{
    char *input = NULL;
    while (1) {
        write(1, "$>", 2), input = get_next_line(0);
        if (input == NULL) {
            write(1, "exit\n", 5);
            break;
        } s_controll->str = separator(input);
        if (my_strcmp(s_controll->str[0], "exit") == 0) {
            write(1, "exit\n", 5);
            break;
        }
        command_parsor(s_controll);
        free_usr_input(s_controll->str), free(input);
    }
    free(input);
}
/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** check
*/

#include "mysh.h"

void free_usr_input(char **str)
{
    for (int i = 0; str[i] != NULL; i++) {
        free(str[i]);
    }
    free(str);
}

int check_if_path(char **str)
{
    for (int i = 0; str[0][i] != '\0'; i++) {
        if (str[0][i] == '/')
            return (1);
    }
    return (0);
}

void check_env(char **envp, controll_t *s_controll)
{
    s_controll->command = 1;
    if (s_controll->str[1] != NULL) {
        write(2, "env: Too many arguments.\n", 25);
        return;
    }
    for (int i = 0; envp[i] != NULL; i++) {
        my_putstr(envp[i]);
        my_putchar('\n');
    }
}
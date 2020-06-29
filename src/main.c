/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** main
*/

#include "mysh.h"

int main(int ac, char **av, char **envp)
{
    controll_t s_controll = {0};
    int len = 0;
    if (ac == 1 && av[1] == NULL) {
        s_controll.envp = envp;
        for (; s_controll.envp[len] != NULL; len++)
            s_controll.head = fill_node(s_controll.head, s_controll.envp[len]);
        shell_loop(&s_controll);
    }
    else if (ac > 2) {
        write(2, "arg error\n", 11);
        return (84);
    }
    return (0);
}

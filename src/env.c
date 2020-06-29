/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** env
*/

#include "mysh.h"

int arg_check(controll_t *s_controll)
{
    int i = 0;
    for (; s_controll->str[i] != NULL; i++);
    if (i == 1) {
        check_env(s_controll->envp, s_controll);
        return (0);
    } if (i > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        return (0);
    } if (!my_isalpha(s_controll->str[1])) {
        write(2,
        "setenv: Variable name must contain alphanumeric characters.\n", 60);
    }
    return (1);
}

int linked_len(env_t *node)
{
    int i = 0;
    while (node != NULL) {
        i++;
        node = node->next;
    }
    return (i);
}

char **linked_to_ptr_array(env_t *node)
{
    int len = linked_len(node), j = 0, l_len = 0, i = 0;
    char **env = malloc(sizeof(char *) * (len + 1));
    for (; node != NULL; i++) {
        j = 0, l_len = my_strlen(node->env_l);
        env[i] = malloc(sizeof(char) * (l_len + 1));
        for (; j < l_len; j++) {
            env[i][j] = node->env_l[j];
        }
        env[i][j] = '\0';
        node = node->next;
    }
    env[i] = NULL;
    return (env);
}

env_t *fill_node(env_t *old, char *line)
{
    env_t *new = malloc(sizeof(env_t));
    new->env_l = line;
    new->next = old;
    return (new);
}

void my_setenv(controll_t *s_controll)
{
    int len = 0;
    s_controll->command = 1;
    s_controll->head = NULL;
    if (!arg_check(s_controll))
        return;
    for (; s_controll->envp[len] != NULL; len++) {
        s_controll->head = fill_node(s_controll->head, s_controll->envp[len]);
    }
    my_setenv_bis(s_controll);
}
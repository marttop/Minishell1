/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** unset_env
*/

#include "mysh.h"

int arg_check2(controll_t *s_controll)
{
    int i = 0;
    for (; s_controll->str[i] != NULL; i++);
    if (i == 1) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return (0);
    }
    return (1);
}

void pop_node(controll_t *s_controll, char *str)
{
    env_t *temp = s_controll->head;
    env_t *old;
    if (my_strncmp(str, temp->env_l, my_strlen(str)) == 0) {
        s_controll->head = temp->next;
        free(temp);
        return;
    }
    while (temp->next != NULL) {
        if (my_strncmp(str, temp->next->env_l, my_strlen(str)) == 0)
            break;
        temp = temp->next;
    }
    if (temp->next != NULL) {
        old = temp->next;
        temp->next = old->next;
        free(old);
    }
}

void my_unsetenv_bis(controll_t *s_controll)
{
    for (int i = 1; s_controll->str[i] != NULL; i++)
        pop_node(s_controll, s_controll->str[i]);
    s_controll->envp = linked_to_ptr_array(s_controll->head);
    rev_ptr(s_controll->envp);
}

void my_unsetenv(controll_t *s_controll)
{
    int len = 0;
    s_controll->head = NULL;
    s_controll->command = 1;
    if (!arg_check2(s_controll))
        return;
    for (; s_controll->envp[len] != NULL; len++) {
        s_controll->head = fill_node(s_controll->head, s_controll->envp[len]);
    }
    my_unsetenv_bis(s_controll);
}
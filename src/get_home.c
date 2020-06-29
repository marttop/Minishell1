/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** get_home
*/

#include "mysh.h"

void go_to_home(controll_t *s_controll, char *home_path)
{
    char *old = NULL;
    old = getcwd(old, 1000);
    update_old_pwd(s_controll, old);
    update_pwd(s_controll, home_path);
    chdir(home_path);
    free(home_path), free(old);
    s_controll->envp = linked_to_ptr_array(s_controll->head);
    rev_ptr(s_controll->envp);
}

char *get_home(char **envp)
{
    int i = 0, a = 0;
    char *home;
    for (; envp[i] != NULL; i++) {
        if (envp[i][0] == 'H' && envp[i][1] == 'O' &&
        envp[i][2] == 'M' && envp[i][3] == 'E')
            break;
    }
    home = malloc(sizeof(char) * my_strlen(envp[i]));
    for (int y = 5; envp[i][y] != '\0'; y++, a++) {
        home[a] = envp[i][y];
    }
    home[a] = '\0';
    return (home);
}

void cat_arg(controll_t *s_controll)
{
    char *new_env_l = malloc(sizeof(char) * 1500);
    new_env_l[0] = '\0';
    my_strcat(new_env_l, s_controll->str[1]), my_strcat(new_env_l, "=");
    if (s_controll->str[2] != NULL) my_strcat(new_env_l, s_controll->str[2]);
    s_controll->head = fill_node(s_controll->head, new_env_l);
}

int check_if_exist(controll_t *s_controll)
{
    char *new_env;
    int i = 0;
    env_t *temp = s_controll->head;
    while (temp != NULL) {
        if (my_strncmp(s_controll->str[1], temp->env_l,
        my_strlen(s_controll->str[1])) == 0) {
            new_env = malloc(sizeof(char) * 1000);
            new_env[0] = '\0';
            my_strcat(new_env, s_controll->str[1]), my_strcat(new_env, "=");
            s_controll->str[2] != NULL ?
            my_strcat(new_env, s_controll->str[2]) : 0;
            temp->env_l = new_env;
            return (1);
        }
        temp = temp->next;
    }
    return (i);
}

void my_setenv_bis(controll_t *s_controll)
{
    if (check_if_exist(s_controll)) {
        s_controll->envp = linked_to_ptr_array(s_controll->head);
        rev_ptr(s_controll->envp);
        return;
    }
    cat_arg(s_controll);
    s_controll->envp = linked_to_ptr_array(s_controll->head);
    rev_ptr(s_controll->envp);
}
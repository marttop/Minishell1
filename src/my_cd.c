/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_cd
*/

#include "mysh.h"

void update_pwd(controll_t *s_controll, char *pwd)
{
    env_t *temp = s_controll->head;
    char *new_pwd = malloc(sizeof(char) * 1000);
    new_pwd[0] = '\0';
    while (temp != NULL) {
        if (my_strncmp("PWD", temp->env_l, 3) == 0) {
            my_strcat(new_pwd, "PWD="), my_strcat(new_pwd, pwd);
            temp->env_l = new_pwd;
            return;
        }
        temp = temp->next;
    }
}

void update_old_pwd(controll_t *s_controll, char *pwd)
{
    env_t *temp = s_controll->head;
    char *new_pwd = malloc(sizeof(char) * 1000);
    new_pwd[0] = '\0';
    while (temp != NULL) {
        if (my_strncmp("OLDPWD", temp->env_l, 6) == 0) {
            my_strcat(new_pwd, "OLDPWD="), my_strcat(new_pwd, pwd);
            temp->env_l = new_pwd;
            return;
        }
        temp = temp->next;
    }
}

void cd_to_old_dir2(controll_t *s_controll, char *old)
{
    env_t *temp = s_controll->head;
    while (temp != NULL) {
        if (my_strncmp("PWD", temp->env_l, 6) == 0) {
            temp->env_l = old;
            break;
        }
        temp = temp->next;
    }
}

void cd_to_old_dir(controll_t *s_controll)
{
    env_t *temp = s_controll->head;
    char *old = NULL, *pwd = NULL, *new = malloc(sizeof(char) * 1000);
    char *new_pwd = NULL;
    pwd = getcwd(pwd, 1000);
    new[0] = '\0';
    while (temp != NULL) {
        if (my_strncmp("OLDPWD", temp->env_l, 6) == 0) {
            old = temp->env_l + 7;
            my_strcat(new, "OLDPWD="), my_strcat(new, pwd);
            temp->env_l = new;
            free(pwd);
        }
        temp = temp->next;
    }
    chdir(old);
    new_pwd = getcwd(new_pwd, 1000);
    update_pwd(s_controll, new_pwd);
    s_controll->envp = linked_to_ptr_array(s_controll->head);
    rev_ptr(s_controll->envp), free(new_pwd);
}

void my_cd(controll_t *s_controll)
{
    int status;
    char *home_path = get_home(s_controll->envp), *old_pwd = NULL, *pwd = NULL;
    s_controll->command = 1;
    if (s_controll->str[1] == NULL) {
        go_to_home(s_controll, home_path);
        return;
    } if (s_controll->str[1] != NULL && s_controll->str[1][0] != '-') {
        old_pwd = getcwd(old_pwd, 1000), status = chdir(s_controll->str[1]);
        if (status == -1) {
            write(2, s_controll->str[0], my_strlen(s_controll->str[0]));
            write(2, ": No such file or directory.\n", 29);
        } else {
            pwd = getcwd(pwd, 1000);
            update_pwd(s_controll, pwd), update_old_pwd(s_controll, old_pwd);
            s_controll->envp = linked_to_ptr_array(s_controll->head);
            rev_ptr(s_controll->envp), free(pwd);
        } free(old_pwd);
    } else if (s_controll->str[1][0] == '-' && s_controll->str[1][1] == '\0')
        cd_to_old_dir(s_controll);
    free(home_path);
}
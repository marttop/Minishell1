/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** mysh
*/

#ifndef MYSH_H_
#define MYSH_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <dirent.h>
#include <errno.h>

typedef struct env {
    char *env_l;
    struct env *next;
} env_t;

typedef struct controll {
    char **envp;
    char **str;
    int command;
    struct env *head;
} controll_t;

char *fill_array(char *str, char *word_array, int *i);
int my_strlen(char const *str);
char **separator(char *str);
void shell_loop(controll_t *s_controll);
int my_strcmp(char const *s1, char const *s2);
int check_if_path(char **str);
void free_usr_input(char **str);
void my_putstr(char const *str);
void my_putchar(char c);
void check_env(char **envp, controll_t *s_controll);
char *get_home(char **envp);
char *my_strdup(char *str);
int my_ptr_len(char **str);
int linked_len(env_t *node);
char **linked_to_ptr_array(env_t *node);
env_t *fill_node(env_t *old, char *line);
void my_setenv(controll_t *s_controll);
void my_cd(controll_t *s_controll);
char *my_strcat(char *dest, char const *src);
void free_double_array(char **str);
int my_isalpha(char *str);
char **rev_ptr(char **str);
void my_setenv_bis(controll_t *s_controll);
int my_strncmp(char const *s1, char const *s2, int n);
void my_unsetenv(controll_t *s_controll);
char **separator_path(char *str);
void path_handling(controll_t *s_controll);
void print_error_msg(controll_t *s_controll);
void my_cd(controll_t *s_controll);
void update_old_pwd(controll_t *s_controll, char *pwd);
void update_pwd(controll_t *s_controll, char *pwd);
void go_to_home(controll_t *s_controll, char *home_path);

#endif /* !MYSH_H_ */
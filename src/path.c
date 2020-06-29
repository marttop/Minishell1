/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** path
*/

#include "mysh.h"

char *fill_array_path(char *str, char *word_array, int *i)
{
    int j = 0;

    word_array = malloc(sizeof(char) * my_strlen(str) + 1);
    for (; str[i[0]] != '\0'; i[0]++, j++) {
        if (str[i[0]] == ':' || str[i[0]] == '=')
            break;
        else
            word_array[j] = str[i[0]];
    }
    word_array[j] = '\0';
    return (word_array);
}

char **separator_path(char *str)
{
    char **word_array = malloc(sizeof(char *) * (my_strlen(str) + 1));
    int i = 0, w = 0;
    if (str == NULL) {
        word_array[0] = NULL;
        return (word_array);
    }
    while (str[i] != '\0') {
        if (str[i] != ':' && str[i] != '=') {
            word_array[w] = fill_array_path(str, word_array[w], &i);
            w++;
        }
        else
            i++;
    }
    word_array[w] = NULL;
    return (word_array);
}

char *get_path(controll_t *s_controll)
{
    env_t *temp = s_controll->head;
    while (temp != NULL) {
        if (my_strncmp("PATH", temp->env_l, 4) == 0) {
            return (temp->env_l);
        }
        temp = temp->next;
    }
    return (NULL);
}

int path_founder(controll_t *s_controll, DIR *dirp)
{
    struct dirent *my_dirent;
    while ((my_dirent = readdir(dirp)) != NULL) {
        if (my_strcmp(my_dirent->d_name, s_controll->str[0]) == 0) {
            return (1);
        }
    }
    return (0);
}

void path_handling(controll_t *s_controll)
{
    DIR *dirp;
    char *my_path = malloc(sizeof(char) * 1000);
    int i = 0, found = 0, id = -300;
    char **path = separator_path(get_path(s_controll));
    if (path == NULL) found = 1;
    for (; path[i] != NULL; i++) {
        dirp = opendir(path[i]);
        if (dirp == NULL) continue;
        if ((found = path_founder(s_controll, dirp)) == 1) break;
        closedir(dirp);
    }
    if (found == 1) {
        my_path[0] = '\0';
        my_strcat(my_path, path[i]), my_strcat(my_path, "/");
        my_strcat(my_path, s_controll->str[0]);
        id = fork();
        if (id == 0) (execve(my_path, s_controll->str, s_controll->envp));
    }
    if (id != -300) wait(&id);
    if (found == 0) print_error_msg(s_controll);
}
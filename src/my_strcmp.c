/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_strcmp
*/

#include "mysh.h"

int my_strcmp(char const *s1, char const *s2)
{
    if (s1 == NULL || s2 == NULL)
        return (84);
    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] < s2[i])
            return (-1);
        else if (s1[i] > s2[i])
            return (1);
    }
    if (my_strlen(s1) < my_strlen(s2))
        return (-1);
    return (0);
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;
    for (; i < n; i++) {
        if (s1[i] < s2[i])
            return (-1);
        else if (s1[i] > s2[i])
            return (1);
    }
    if (s2[i] != '=')
        return (-1);
    return (0);
}

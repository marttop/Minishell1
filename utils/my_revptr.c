/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_revptr
*/

#include "mysh.h"

char **rev_ptr(char **str)
{
    char *temp;
    int len = my_ptr_len(str) - 1;
    for (int i = 0; i < len; i++, len--) {
        temp = str[i];
        str[i] = str[len];
        str[len] = temp;
    }
    return (str);
}
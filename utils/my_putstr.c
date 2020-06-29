/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_putstr
*/

#include "mysh.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    if (str == NULL)
        return;
    for (int i = 0; str[i] != '\0'; i++)
        my_putchar(str[i]);
}

void print_error_msg(controll_t *s_controll)
{
    write(2, s_controll->str[0], my_strlen(s_controll->str[0]));
    write(2, ": Command not found.\n", 21);
}

int my_isalpha(char *str)
{
    int i = 0;
    for (; str[i] != '\0'; i++) {
        if (!(str[i] <= '9' && str[i] >= '0') && !(str[i] >= 'A' &&
        str[i] <= 'Z') && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] == '_'))
            return (0);
    }
    return (1);
}
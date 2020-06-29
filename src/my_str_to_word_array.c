/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_str_to_word_array
*/

#include "mysh.h"

char *fill_array(char *str, char *word_array, int *i)
{
    int j = 0;

    word_array = malloc(sizeof(char) * my_strlen(str) + 1);
    for (; str[i[0]] != '\0'; i[0]++, j++) {
        if (str[i[0]] == ' ' || str[i[0]] == '\t')
            break;
        else
            word_array[j] = str[i[0]];
    }
    word_array[j] = '\0';
    return (word_array);
}

char **separator(char *str)
{
    char **word_array = malloc(sizeof(char *) * (my_strlen(str) + 1));
    int i = 0, w = 0;

    while (str[i] != '\0') {
        if (str[i] != '\t' && str[i] != ' ') {
            word_array[w] = fill_array(str, word_array[w], &i);
            w++;
        }
        else
            i++;
    }
    word_array[w] = NULL;
    return (word_array);
}

/*
** EPITECH PROJECT, 2019
** CPE_getnextline_2019
** File description:
** get_next_line
*/

#include "get_next_line.h"

int my_strlen(char const *str)
{
    int i = 0;
    if (str == NULL)
        return (1);
    while (str[i] != '\0')
        i++;
    return (i);
}

char *check_result(char *result)
{
    if (result[0] == '\0')
        return (NULL);
    else
        return (result);
}

char *my_strncat(char *dest, char *src, int nb, junk_t *my_junk)
{
    int i = 0, a = 0;
    int len = my_strlen(dest);

    if (dest[0] == '\n')
        return (after_line(dest, src, my_junk));
    for (; a < nb; a++) {
        if (src[a] == '\n') {
            my_junk->state = 1;
            break;
        }
    }
    for (; i < a && src[i] != '\0'; i++) {
        dest[len + i] = src[i];
    }
    dest[len + i] = '\0';
    my_junk->back = 0;
    return (dest);
}

char *after_line(char *result, char *temp, junk_t *my_junk)
{
    int i = 0;
    static int s = 0;
    for (; temp[s] != '\0'; s++) {
        if (temp[s] == '\n') {
            s++;
            break;
        }
    }
    for (; temp[s] != '\0'; s++, i++) {
        if (temp[s] == '\n') {
            my_junk->state = 1;
            break;
        }
        else
            result[i] = temp[s];
    }
    if (s >= READ_SIZE)
        s = 0;
    result[i] = '\0';
    return (result);
}

char *get_next_line(int fd)
{
    static char temp[READ_SIZE + 1];
    junk_t my_junk;
    int len = READ_SIZE;
    char *result = malloc(sizeof(char) * 1000);
    if (result == NULL || fd == -1)
        return (NULL);
    result[0] = '\0';
    my_junk.state = 0;
    if (temp[0] != 0)
        result = after_line(result, temp, &my_junk);
    while (my_junk.state == 0) {
        if ((len = read(fd, temp, len)) > 0) {
            temp[len] = '\0';
            result = my_strncat(result, temp, len, &my_junk);
        }
        else
            return (check_result(result));
    }
    return (result);
}

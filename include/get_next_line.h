/*
** EPITECH PROJECT, 2019
** CPE_getnextline_2019
** File description:
** get_next_line
*/

#ifndef GET_NEXT_LINE_H_
#define GET_NEXT_LINE_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef READ_SIZE
#define READ_SIZE 12
#endif /* READ_SIZE */

typedef struct junk {
    int state;
    int back;
} junk_t;

char *get_next_line(int fd);
char *after_line(char *result, char *temp, junk_t *my_junk);
char *my_strncat(char *dest, char *src, int nb, junk_t *my_junk);
char *check_result(char *result);
int my_strlen(char const *str);


#endif /* !GET_NEXT_LINE_H_ */

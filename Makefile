##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile
##

NAME	=	mysh

CC	=	gcc

SRC	=	src/main.c \
		src/my_str_to_word_array.c \
		src/get_next_line.c \
		src/shell_loop.c \
		src/my_strcmp.c \
		src/check.c \
		src/get_home.c \
		src/env.c \
		src/unset_env.c \
		src/path.c \
		src/my_cd.c \
		utils/my_putstr.c \
		utils/my_strcat.c \
		utils/my_strdup.c \
		utils/ptr_len.c \
		utils/my_revptr.c \

SRC_TEST	=	tests/test.c \


OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra
CFLAGS	+=	-I./include -g3 -O0
FFLAGS = -L/usr/local/lib -lcriterion --coverage
FFLAGS += -fprofile-arcs -ftest-coverage

all	:	$(NAME)

tests_run :
	$(CC) -o test_run -O0 $(CFLAGS) $(FFLAGS) $(SRC_TEST)
	./test_run
coverage :
	/home/mszuts/.local/bin/gcovr --branch --exclude tests/
$(NAME)	:	$(OBJ)
		gcc -o $(NAME) $(OBJ)
clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)
		rm -f *gcda *gcno test_run

re	:	fclean all

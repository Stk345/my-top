##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## All usefull command for compiling
##

SRC	=	lib/my/my_putchar.c	\
		lib/my/my_putstr.c	\
		lib/my/my_put_nbr.c	\
		lib/my/my_strlen.c	\
		lib/my/my_strncpy.c	\
		top_header/uptime.c		\
		my_top.c		\
		top_columns/tasks.c		\
		top_columns/time.c		\
		top_header/cpu_header.c	\
		top_columns/process_status.c	\
		top_header/mib_mem.c	\
		top_header/mib_swap.c	\
		top_columns/user.c	\
		top_header/header_user.c	\
		top_header/load_average.c	\
		top_header/tasks_header.c	\
		top_columns/get_pr_and_nice.c	\
		top_columns/get_virt_and_res.c	\
		top_columns/cpu_process.c	\
		top_columns/mem_percent.c


OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -lncurses main.c $(SRC) -o my_top

tests_run:
	epiclang --coverage -lcriterion -lncurses -lgcov -lm tests/*.c $(SRC) -o test_unit
	./test_unit

tests_covr:
	gcovr --gcov-executable "llvm-cov-20 gcov" --exclude "tests/.*"
	gcovr --branches --gcov-executable "llvm-cov-20 gcov" --exclude "tests/.*"
	rm *.gcda *.gcno

clean:
	rm -f *.o
	rm -f lib/my/*.o
	rm -f top_columns/*.o
	rm -f top_header/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

auteur:
	echo $(USER) > auteur

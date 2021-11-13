SRCS = main.c
C.O = ${SRCS:.c=.o}
H = fdf.h
NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror
LEAK = -fsanitize=address

all : $(NAME)

$(NAME) :
	$(CC) $(FLAGS) $(SRCS) -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
# 	valgrind ./fdf

leak :
	$(CC) $(FLAGS) $(LEAK) $(SRCS) -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

clean :
	rm -f $(C.O)

fclean : clean
	rm -f $(NAME)

re : fclean all

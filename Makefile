SRCS = main.c get_next_line.c
C.O = ${SRCS:.c=.o}
H = fdf.h
NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror
LEAK = -fsanitize=address

all : $(NAME)

$(NAME) :
	$(CC) $(FLAGS) -D BUFFER_SIZE=1 $(SRCS) -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME) #just remove "-D BUFFER_SIZE=1"
# 	valgrind ./fdf

leak :
	$(CC) $(FLAGS) $(LEAK) -D BUFFER_SIZE=1 $(SRCS) -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -o fdfleak

clean :
	rm -f $(C.O)

fclean : clean
	rm -f $(NAME)

re : fclean all

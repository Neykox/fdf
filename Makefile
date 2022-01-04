SRCS = main.c get_next_line.c libft.c
SRCS2 = main3.c get_next_line.c libft.c bresenham.c
SRCS4 = main4.c get_next_line.c libft.c bresenham4.c
C.O = ${SRCS:.c=.o}
H = fdf.h
NAME = fdf
NAME2 = fdf2
NAME4 = fdf4
CC = gcc
FLAGS = -Wall -Wextra -Werror
LEAK = -fsanitize=address

all : $(NAME)

$(NAME) :
	$(CC) $(FLAGS) -D BUFFER_SIZE=1 $(SRCS) -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME) #just remove "-D BUFFER_SIZE=1"
# 	valgrind ./fdf

2 :
	$(CC) $(FLAGS) -D BUFFER_SIZE=1 $(SRCS2) -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME2)

4 :
	$(CC) $(FLAGS) -D BUFFER_SIZE=1 $(SRCS4) -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME4)

leak :
	$(CC) $(FLAGS) $(LEAK) -D BUFFER_SIZE=1 $(SRCS) -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -o fdfleak

clean :
	rm -f $(C.O)

fclean : clean
	rm -f $(NAME)

re : fclean all

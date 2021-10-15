SRCS = main.c
C.O = ${SRCS:.c=.o}
H = fdf.h
NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror     # -framework OpenGL -framework AppKit
LEAK = -fsanitize=address

#linux?
# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

# $(NAME): $(OBJ)
# 	$(CC) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

# 	$(CC) main.c -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz
#supposement mac
# %.o: %.c
# 	$(CC) $(FLAGS) -Imlx -c $< -o $@

# $(NAME): $(OBJ)
# 	$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all : $(NAME)

$(NAME) :
	$(CC) $(FLAGS) $(SRCS) -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

# $(NAME) :
# 	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

leak :
	$(CC) $(FLAGS) $(LEAK) $(SRCS) -L./mlx_linux -lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

clean :
	rm -f $(C.O)

fclean : clean
	rm -f $(NAME)

re : fclean all

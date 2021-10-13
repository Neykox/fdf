SRCS = main.c
C.O = ${SRCS:.c=.o}
H = fdf.h
NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror     # -framework OpenGL -framework AppKit

#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

#$(NAME): $(OBJ)
#	$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all : $(NAME)

$(NAME) :
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean :
	rm -f $(C.O)

fclean : clean
	rm -f $(NAME)

re : fclean all

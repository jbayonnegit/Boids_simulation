NAME = boids
SRC =	boids.c \
		boids_init.c \
		free.c \
		main.c \
		window.c \
		utils.c \
		quadtree.c \
		rules.c \

CFLAGS = -Wall -Wextra -Werror
CC = cc
OBJ_DIR = obj
SRC_DIR = src

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				@mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -I.  -fsanitize=address -lasan -g3 -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CFLAGS) -lSDL2 -fsanitize=address -g3 -lm

clean :
		rm -f -r $(OBJ_DIR)

fclean : clean
		rm -f $(NAME)

re : fclean all

.PHONY : fclean clean all ren
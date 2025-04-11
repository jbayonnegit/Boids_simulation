NAME = boids
SRC =	boids.c \
		boids_init.c \
		free.c \
		main.c \
		window.c \
		utils.c \
		quadtree.c \
		rules.c \

CC = cc
CFLAGS = -Wall -Wextra -Iinclude -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lm
OBJ_DIR = obj
SRC_DIR = src

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -g3 -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -g3

clean :
	rm -f -r $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : fclean clean all re

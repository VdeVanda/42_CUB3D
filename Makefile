NAME = cub3D

SRCS = debug.c srcs/init.c srcs/map.c srcs/player.c srcs/move.c srcs/rays.c srcs/create.c \
	   srcs/walls.c srcs/cleanup.c \
	   srcs/parsing/check_map.c srcs/parsing/map_loading.c srcs/parsing/parse_colors.c \
	   srcs/parsing/parse_header.c srcs/parsing/parse_main.c srcs/parsing/parse_utils.c \


OBJS = $(SRCS:.c=.o)

HEADER = cub3D.h

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Paths
INCLUDES_PATH = ./includes
MLX_PATH = $(INCLUDES_PATH)/minilibx-linux
LIBFT_PATH = $(INCLUDES_PATH)/libft

# Libs
MLX_NAME = mlx
MLX_LIB = $(MLX_PATH)/lib$(MLX_NAME).a

LIBFT_NAME = ft
LIBFT_LIB = $(LIBFT_PATH)/lib$(LIBFT_NAME).a

LIBS = -L$(MLX_PATH) -l$(MLX_NAME) -L$(LIBFT_PATH) -l$(LIBFT_NAME) -lXext -lX11 -lm -lz
INCLUDES = -I$(MLX_PATH) -I$(LIBFT_PATH)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(MLX_PATH)
	@make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(MLX_PATH) clean
	@make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re

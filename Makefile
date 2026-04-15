NAME = cub3D
SHELL = /bin/bash

SRCS = main.c srcs/init.c srcs/player.c srcs/move.c srcs/rays.c \
	   srcs/ray_cast.c srcs/create.c srcs/walls.c srcs/cleanup.c srcs/resource.c \
	   srcs/input.c srcs/render_utils.c \
	   srcs/parsing/check_map.c srcs/parsing/map_loading.c srcs/parsing/parse_colors.c \
	   srcs/parsing/parse_header.c srcs/parsing/parse_main.c srcs/parsing/parse_utils.c \


OBJS = $(SRCS:.c=.o)

HEADER = cub3D.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -Wno-incompatible-pointer-types

# Cores
GREEN = \033[1;32m
RESET = \033[0m

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
INCLUDES = -isystem $(MLX_PATH) -I$(LIBFT_PATH)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "🔨 Building minilibx..."
	@make -C $(MLX_PATH) -s -f Makefile.mk all INC=/usr/include CC="gcc -std=gnu89"
	@echo "🔨 Building libft..."
	@make -C $(LIBFT_PATH) -s
	@echo "🔗 Linking cub3D..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -no-pie -o $(NAME)
	@echo -e "$(GREEN)  ✓ $(NAME) built successfully$(RESET)"

%.o: %.c $(HEADER)
	@echo "📝 Compiling $(notdir $<)..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(MLX_PATH) -s -f Makefile.mk clean
	@make -C $(LIBFT_PATH) clean -s

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean -s
	@echo "Goodbye!"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus

NAME = cub3D

SRCS = main.c srcs/init.c srcs/map.c srcs/player.c srcs/move.c srcs/rays.c srcs/create.c \
	   srcs/walls.c srcs/cleanup.c srcs/resource.c srcs/input.c srcs/render_utils.c \
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
INCLUDES = -isystem $(MLX_PATH) -I$(LIBFT_PATH)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "🔨 Building minilibx..."
	@make -C $(MLX_PATH) -s > /dev/null 2>&1
	@echo "🔨 Building libft..."
	@make -C $(LIBFT_PATH) -s
	@echo "🔗 Linking cub3D..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\033[1;32m  ✓ $(NAME) built successfully\033[0m"

%.o: %.c $(HEADER)
	@echo "📝 Compiling $(notdir $<)..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(MLX_PATH) clean -s > /dev/null 2>&1
	@make -C $(LIBFT_PATH) clean -s

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean -s
	@echo "Goodbye!"

re: fclean all

.PHONY: all clean fclean re

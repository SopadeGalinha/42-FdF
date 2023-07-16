.SILENT:

NAME = fdf

SRC_DIR = ./srcs
MLX_DIR = ./includes/minilibx
LIBFT_DIR = ./includes/libft

SRC_FILES = main.c
MLX_FILES = ./includes/libmlx.a

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -L$(MLX_DIR) -L$(LIBFT_DIR)
LDLIBS = -lX11 -lXext -lmlx -lft
INCLUDES = -Iincludes -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

$(OBJS): | $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

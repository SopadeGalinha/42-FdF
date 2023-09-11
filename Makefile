.ONESHELL:

NAME = fdf

SRCS_DIR = srcs/
OBJS_DIR = srcs/objs/
LIBFT_DIR = includes/libft/
MLX_DIR = includes/minilibx/

SRCS_LIST = main.c init.c init_utils.c \
            set_display.c set_graphics.c render.c draw.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LIST:.c=.o))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

MLX = $(addprefix $(MLX_DIR), libmlx.a)

CC = cc
RM = rm -rf
CFLAGS = -g # -Wall -Wextra -Werror

COMMIT_MESSAGE = "auto commit"

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	$(RM) $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

re: fclean all

git:
ifdef MESSAGE
	$(eval COMMIT_MESSAGE = "$(MESSAGE)")
endif
	git add .
	git commit -m $(COMMIT_MESSAGE)
	git push

norm:
	norminette $(SRCS) includes/*.h
.PHONY: all clean fclean re git norm

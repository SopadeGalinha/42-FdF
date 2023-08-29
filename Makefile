# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 20:04:30 by jhogonca          #+#    #+#              #
#    Updated: 2023/08/29 18:48:56 by jhoonca          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS_LIST = main.c initialization.c ft_atoi_base.c init_utils.c

SRCS_DIR = srcs/
OBJS_DIR = srcs/objs/
LIBFT_DIR = includes/libft/

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LIST:.c=.o))

LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
MLX	= $(addprefix $(MLX_DIR), libmlx.a)
MLX_DIR = includes/minilibx/

CC = cc
RM = rm -rf
CFLAGS = -g #-fsanitize=address

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -o $(NAME) -lm

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
#	make clean -C $(MLX_DIR)

re: fclean all

norm:
	norminette $(SRCS) includes/*.h
.PHONY: all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhoonca <jhogonca@student.42porto.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 20:04:30 by jhogonca          #+#    #+#              #
#    Updated: 2023/08/12 18:24:04 by jhoonca          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS_LIST = main.c initialization.c ft_atoi_base.c init_utils.c

SRCS_DIR = srcs/
LIBFT_DIR = includes/libft/

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
MLX	= $(addprefix $(MLX_DIR), libmlx.a)
MLX_DIR = includes/minilibx/

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(SRCS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -o $(NAME)

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
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 20:04:30 by jhogonca          #+#    #+#              #
#    Updated: 2023/07/25 20:04:31 by jhogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = fdf

SRCS_LIST = main.c

SRCS_DIR = srcs/
OBJS_DIR = objs/
LIBFT_DIR = includes/libft/

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LIST:.c=.o))

LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
LIBMLX_DIR = includes/minilibx/
LIBMLX = $(addprefix $(LIBMLX_DIR), libmlx.a)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(LIBMLX_DIR) -lmlx -lX11 -lXext -lm -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBMLX):
	make -C $(LIBMLX_DIR)

clean:
	$(RM) $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(LIBMLX_DIR)

re: fclean all

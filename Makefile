# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 05:46:56 by jhogonca          #+#    #+#              #
#    Updated: 2023/06/17 23:53:28 by jhogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#.SILENT:

NAME = fdf

SRC_DIR = ./minilibft
MLX_DIR = ./minilibx

SRC_FILES = ft_printf.c get_next_line.c ft_split.c
MLX_FILES = libmlx.a

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES)) main.c
OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = 
LDFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext
INCLUDES = -Iincludes -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

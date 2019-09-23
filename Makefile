# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inazarin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/25 14:37:53 by inazarin          #+#    #+#              #
#    Updated: 2018/09/25 14:37:55 by inazarin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS = main.c \
		parsing.c \
		movement.c \
		movement_two.c \
		drawing.c \
		helper.c \
		write_n_free.c

		

OBJ =	$(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = fdf.h



all: $(NAME)

%.o:%.c
	gcc -I. $(FLAGS) -g -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	make -C libft
	gcc  $(FLAGS) $(MLX_FLAGS) $(OBJ) libft/libft.a -o $(NAME) 

clean:
	make clean -C libft/
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft/
	rm -f libft.a
	rm -f $(NAME)

re: fclean all

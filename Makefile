# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xortega <xortega@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 13:12:01 by xortega           #+#    #+#              #
#    Updated: 2024/01/24 14:21:38 by xortega          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long
CC				:= gcc
CFLAGS			:= -Wall -Wextra -Werror -lreadline -I ./includes
SOURCES			:= so_long.c so_map.c so_tiles.c so_checks.c so_exits.c so_mlx.c so_movements.c
OBJECTS			:= $(SOURCES:.c=.o)
LIBFT			:= libft.a
MLX				:= libmlx.a

all: $(NAME)

.SILENT:

$(NAME): $(LIBFT) $(MLX) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -Lmlx -framework OpenGL -framework AppKit $(MLX) $(LIBFT) -o $(NAME)
	chmod 777 $(NAME)

$(LIBFT):
	@make -C Libft 2> /dev/null
	cp Libft/libft.a $(LIBFT)
	
$(MLX):
	@make -C mlx 2> /dev/null
	cp mlx/libmlx.a $(MLX)

clean:
	make clean -C Libft
	make clean -C mlx
	rm -f $(OBJECTS)

fclean: clean
	printf "\033[1;31m❌ERASED❌\n"
	rm -f $(NAME)
	rm -f libft.a
	rm -f libmlx.a

rclean:	clean
	printf "✅REMAKE✅\n"
	rm -f $(NAME)
	rm -f libft.a
	rm -f libmlx.a

re: rclean all

.PHONY: all rclean clean fclean re
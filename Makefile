# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 12:32:15 by luiberna          #+#    #+#              #
#    Updated: 2024/03/25 15:27:44 by luiberna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS = fdf.c init.c verifiers.c free.c map.c draw_alg.c projections.c color.c keys.c rotations.c

CC = cc

OBJS = $(SRCS:.c=.o)

INCLUDE = ./Includes/

CFLAGS = -I$(INCLUDE) -g -I$(MINILIBX) -O3 -Wall -Wextra -Werror
 

RM = rm -f

LIB_MINILIBX = $(MINILIBX)/libmlx_Linux.a -L$(MINILIBX) -L/usr/lib -I$(MINILIBX) -lXext -lX11 -lm -lz

MINILIBX = ./minilibx/

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./Libft
	make -C $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_MINILIBX) ./Libft/libft.a -o $(NAME)

clean:
	make clean -C ./Libft
	make clean -C $(MINILIBX)
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./Libft
	make clean -C $(MINILIBX)
	rm -f $(NAME)

re: fclean $(NAME)

r: 
	make re && ./fdf 

.PHONY: all clean fclean re



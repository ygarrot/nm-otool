# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2018/12/30 14:40:28 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm 

FLAGS = -Wall -Werror -Wextra -g3
FLAGS +=  -fsanitize=address

SRC_FOLDER = src/
INCLUDE =  includes/
OBJ_DIR = mkdir obj
# :r !ls
SRC_FP =\
				segment_command.c \
				ptr_utils.c \
				ft_hashcmp.c \
		nlist.c \
		nm.c
OBJ = $(addprefix $(SRC_FOLDER), $(SRC_FP:.c=.o))
LIBFT = ../libft/libft.a

all: $(NAME)

src/%.o: src/%.c

	@gcc $(FLAGS) -o $@ -c $<  -I $(INCLUDE)

$(NAME): $(OBJ)
	@make -C ../libft -j
	@gcc $(FLAGS) -o $(NAME) $(OBJ) -I $(INCLUDE) -L ../libft -l ft

clean:
	@rm -f $(OBJ)
	@make -C ../libft clean

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -f $(NAME_NO_HOST)
	@make -C ../libft fclean

re: fclean all

.PHONY: $(NAME) all clean fclean re

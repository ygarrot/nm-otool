# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2018/12/24 13:17:12 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm 

FLAGS =-Wall -Werror -Wextra -g3

SRC_FOLDER = src/
INCLUDE =  includes/
OBJ_DIR = mkdir obj
SRC_FP = \

OBJ = $(addprefix $(SRC_FOLDER), $(SRC_FP:.c=.o))
LIBFT = libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@gcc $(FLAGS) -o $@ -c $< -I $(INCLUDE)

$(NAME): $(OBJ)
	@make -C libft -j
	@gcc $(FLAGS) -o $(NAME) $(OBJ) -L libft -l ft

clean:
	@rm -f $(OBJ)
	@make -C libft clean

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -f $(NAME_NO_HOST)
	@make -C libft fclean

re: fclean all

.PHONY: $(NAME) all clean fclean re

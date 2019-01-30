# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/01/29 12:26:04 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm-otool 

all: $(NAME)

$(NAME): $(OBJ)
	@make -C nm 
	@make -C otool 

clean:
	@make -C nm
	@make -C otool 

fclean:
	make -C nm fclean
	make -C otool fclean

re: fclean all

.PHONY: $(NAME) all clean fclean re

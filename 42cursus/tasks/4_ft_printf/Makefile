# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: twilford <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 20:17:17 by twilford          #+#    #+#              #
#    Updated: 2021/01/02 20:17:24 by twilford         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HDR = libftprintf.h

NAME = libftprintf.a

SRCS =	ft_printf.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

RM = rm -f

CC = gcc -c

ARRC = ar rc

RLIB = ranlib

all:		$(NAME)

%.o: %.c
			$(CC) $(FLAGS) $< -o $@

$(NAME):	$(OBJS) $(HDR)
			$(ARRC) $(NAME) $?
			$(RLIB) $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			
re:			fclean all

#re%:
#    		make fclean
#    		make $(patsubst re%, %, $@)

.PHONY:		all clean fclean re

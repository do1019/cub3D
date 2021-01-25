# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/02 08:42:26 by dogata            #+#    #+#              #
#    Updated: 2020/12/24 02:54:05 by dogata           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS := -Wall -Wextra -Werror
LIBS := ar rcs
NAME := get_next_line.a
SRCS := get_next_line.c get_next_line_utils.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)
 
$(NAME): $(OBJS)
	@$(LIBS) $(NAME) $(OBJS)

$(OBJS_BONUS): $(OBJS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
 
fclean: clean
	rm -f $(NAME)
 
re: fclean all
 
.PHONY: all bonus clean fclean re
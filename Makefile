# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 20:19:48 by hoskim            #+#    #+#              #
#    Updated: 2025/06/16 20:21:01 by hoskim           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iincludes -Isrc/expander -Isrc/lexer -Isrc/parser -Isrc/signal -Isrc/utils -Isrc/builtin -Isrc/executor

SRCS_DIR = src
SRCS = $(wildcard $(SRCS_DIR)/**/*.c) $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

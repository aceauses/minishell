# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 15:35:32 by aceauses          #+#    #+#              #
#    Updated: 2023/11/27 16:15:12 by aceauses         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl
CC = gcc
AR = ar rcs
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

BOLD    := \033[1m./SRC/
RED     := \033[31;1m
GREEN   := \033[32;1m
YELLOW  := \033[33;1m
BLUE    := \033[34;1m
MAGENTA := \033[35;1m
CYAN    := \033[36;1m
WHITE   := \033[37;1m
RESET	= \x1b[0m


all: $(NAME)

$(OBJS): $(SRCS)
	@$(CC) -c $(CFLAGS) $(SRCS)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(CYAN)[GNL] $(GREEN)Library Compiled$(RESET)"

clean:
	@$(RM) $(OBJS)
	@echo "$(CYAN)[GNL] $(RED)Objects Cleaned$(RESET)"

fclean:
	@$(RM) $(OBJS) $(NAME)
	@echo "$(CYAN)[GNL] $(RED)Library, Objects Cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re
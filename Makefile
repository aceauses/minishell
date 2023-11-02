# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 09:14:51 by aceauses          #+#    #+#              #
#    Updated: 2023/11/02 15:26:30 by aceauses         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_OF_PROJECT = minishell
CC = cc
READLINE = $(HOME)/.brew/opt/readline
LDFLAG = -L $(READLINE)/lib -lreadline
INCFLAGS = -I $(READLINE)/include
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -I . -MMD -MP
RM = rm -rf

UTILS_DIR = src/
UTILS = $(UTILS_DIR)functions/ft_exit.c \
		$(UTILS_DIR)parser/ft_test.c

UTILS_OBJS = $(patsubst %.c, $(OBJS_DIR)%.o, $(notdir $(UTILS)))
SRC = minishell.c

OBJS_DIR = OBJS/
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRC:.c=.o))) $(UTILS_OBJS)

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

$(OBJS_DIR)%.o: $(UTILS_DIR)functions/%.c
	@echo "$(YELLOW)Compiling:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(OBJS_DIR)%.o: $(UTILS_DIR)parser/%.c
	@echo "$(YELLOW)Compiling:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(OBJS_DIR)%.o: %.c
	@echo "$(YELLOW)Main:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiled with $(CYAN)$(CFLAGS)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAG)

clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(CYAN)[$(NAME_OF_PROJECT)] $(RED)Objects Cleaned$(RESET)"

fclean:
	@$(RM) $(NAME) $(OBJS_DIR)
	@echo "$(CYAN)[$(NAME_OF_PROJECT)] $(RED)Executable, Objects Cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re%
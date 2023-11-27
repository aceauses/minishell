# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 09:14:51 by aceauses          #+#    #+#              #
#    Updated: 2023/11/27 16:07:40 by aceauses         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_OF_PROJECT = minishell
CC = cc
LIBFT = libft/libft.a
GNL = get_next_line/gnl
PRINTF = dprintf/dprintf.a
READLINE = $(shell brew --prefix readline)
LDFLAG = -L $(READLINE)/lib -lreadline
INCFLAGS = -I $(READLINE)/include
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I . -MMD -MP
RM = rm -rf

UTILS_DIR = src/
UTILS = $(UTILS_DIR)functions/ft_error.c \
		$(UTILS_DIR)functions/ft_signals.c \
		$(UTILS_DIR)functions/ft_free.c \
		$(UTILS_DIR)executor/ft_executor.c \
		$(UTILS_DIR)executor/ft_single_cmd.c \
		$(UTILS_DIR)executor/ft_multiple_cmds.c \
		$(UTILS_DIR)executor/ft_handle_redirs.c \
		$(UTILS_DIR)builtins/ft_env.c \
		$(UTILS_DIR)builtins/ft_exit.c \
		$(UTILS_DIR)builtins/ft_echo.c \
		$(UTILS_DIR)builtins/ft_export.c \
		$(UTILS_DIR)builtins/ft_pwd.c \
		$(UTILS_DIR)builtins/ft_unset.c \
		$(UTILS_DIR)builtins/ft_builtins.c \
		$(UTILS_DIR)lexer/ft_lexer.c \
		$(UTILS_DIR)lexer/ft_lexer_utils.c \
		$(UTILS_DIR)lexer/ft_lexer_utils2.c \
		$(UTILS_DIR)builtins/ft_cd.c \
		$(UTILS_DIR)shell/ft_prompt.c \
		$(UTILS_DIR)shell/empty_env.c \
		$(UTILS_DIR)parser/ft_parser.c \
		$(UTILS_DIR)parser/ft_parser_utils.c \
		$(UTILS_DIR)parser/ft_parser_utils2.c \
		$(UTILS_DIR)parser/ft_token_utils.c \
		$(UTILS_DIR)parser/ft_cmd_table.c \
		$(UTILS_DIR)parser/ft_cmd_table_utils.c \
		$(UTILS_DIR)parser/ft_cmd_table_utils2.c \
		$(UTILS_DIR)parser/ft_remove_quotes.c \
		$(UTILS_DIR)test/ft_pipe.c \
		$(UTILS_DIR)test/ft_error_pipex.c \
		$(UTILS_DIR)test/pipex.c \
		$(UTILS_DIR)test/ft_bonus.c 

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

$(OBJS_DIR)%.o: $(UTILS_DIR)executor/%.c
	@echo "$(YELLOW)Compiling:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(OBJS_DIR)%.o: $(UTILS_DIR)lexer/%.c
	@echo "$(YELLOW)Compiling:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(OBJS_DIR)%.o: $(UTILS_DIR)builtins/%.c
	@echo "$(YELLOW)Compiling:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(OBJS_DIR)%.o: $(UTILS_DIR)test/%.c
	@echo "$(YELLOW)Compiling:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(OBJS_DIR)%.o: $(UTILS_DIR)shell/%.c
	@echo "$(YELLOW)Compiling:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(OBJS_DIR)%.o: $(UTILS_DIR)parser/%.c
	@echo "$(YELLOW)Compiling:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(OBJS_DIR)%.o: $(UTILS_DIR)tokenizer/%.c
	@echo "$(YELLOW)Compiling:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(OBJS_DIR)%.o: %.c
	@echo "$(YELLOW)Main:$(RESET) $(BLUE)$<$(RESET)"
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $< $(CPPFLAGS) $(INCFLAGS)

$(GNL):
	@make -C get_next_line all

$(PRINTF):
	@make -C dprintf all

$(NAME): $(LIBFT) $(GNL) $(PRINTF) $(OBJS)
	@echo "$(GREEN)Compiled with $(CYAN)$(CFLAGS)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAG) $(LIBFT) $(GNL) $(PRINTF)

$(LIBFT):
# ifeq ($(shell uname), Darwin)
# 	@git submodule update --init --recursive --remote
# endif
	@make -C libft all

clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(CYAN)[$(NAME_OF_PROJECT)] $(RED)Objects Cleaned$(RESET)"
	@make -C get_next_line clean
	@make -C dprintf clean
	@make -C libft clean

fclean:
	@$(RM) $(NAME) $(OBJS_DIR)
	@echo "$(CYAN)[$(NAME_OF_PROJECT)] $(RED)Executable, Objects Cleaned$(RESET)"
	@make -C get_next_line fclean
	@make -C dprintf fclean
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
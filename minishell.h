/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:47 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/03 17:57:51 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "libft/libft.h"

// colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

typedef struct s_shell
{
	char			**env;
	char			**path;
	char			*line;
	char			**req; // splitted argument after pipes
	struct termios	saved;
}					t_shell;

// 
void	xerror(char *s, void *data);

void	ft_free(char **s);

void	prepare_prompt(void);

void	ft_getreq(t_shell *shell);

//SIGNALS
void	check_signals(struct termios *saved);
void	ctrl_c_settings(void);
void	ctrl_slash_settings(void);
void	handle_ctrl_c(int signal, siginfo_t *info, void *x);
void	handle_ctrl_slash(int signal, siginfo_t *info, void *x);

#endif
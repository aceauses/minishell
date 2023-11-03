/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:47 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/03 18:25:11 by aceauses         ###   ########.fr       */
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

//pipex
# include <unistd.h>
# include <time.h>
# include <fcntl.h>
int		pipex(char **argv, char *ev[]);
int		check_access(char *argv, char c);
/*Path Finder*/
char	*find_path(char **path, char *command);

/*Child Process*/
void	child_one(char *argv, char **ev, int p[2]);

/*Child Two Process*/
void	child_two(char *argv, char **ev, int p[2]);

/*Free handle*/
char	*free_join(char *buffer, char *buff);
void	ft_free_array(char **array);

/*Error handle*/
void	error(const char *s, char *s2);
/*Bonus*/
char	**special_command(char *argv);
//-----

//Redirections types
# define R_INPUT 1
# define R_OUTPUT 2
# define R_APPEND 3
# define R_HEREDOC 4

// redirs
typedef struct s_redir
{
	char	*file; // Here we store the file name
	int		type; // Here we store the type of redirection
}				t_redir;

typedef struct s_shell
{
	char	**env;
	char 	**path;
	char 	*line;
	char	**req; // splitted argument after pipes
	char	*status_s;
	char	*status_f;
	char	*current_status;
	int		status;
	struct termios	saved;
}					t_shell;

// 
void	xerror(char *s, void *data);

void	ft_free(char **s);

void	prepare_prompt(t_shell *shell);

void	ft_getreq(t_shell *shell);

int	env_print(char *line, t_shell *shell);

int	check_builtins(char *line, t_shell *shell);
int check_exit(char *line);
int	pwd_print(char *line, t_shell *shell);

// colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"
//SIGNALS
void	check_signals(struct termios *saved);
void	ctrl_c_settings(void);
void	ctrl_slash_settings(void);
void	handle_ctrl_c(int signal, siginfo_t *info, void *x);
void	handle_ctrl_slash(int signal, siginfo_t *info, void *x);

#endif
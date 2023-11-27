/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:47 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/27 15:57:15 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "dprintf/ft_printf.h"

# define SPACES " \t\n\v\r\f"

//##########################ERRORS#############################################
# define BAD_PIPE "Error: syntax error near unexpected token `|'\n"
# define BUILTINS "echo cd pwd export unset env exit history"
# define IS_QUOTE(x) (x == '"' || x == '\'')
# define SQUOTE 39
# define DQUOTE 34
# define PIPE "|"

//pipex
# include <unistd.h>
# include <time.h>
# include <fcntl.h>

int			pipex(char **argv, char *ev[]);
int			check_access(char *argv, char c);
/*Path Finder*/
char		*find_path(char **path, char *command);

/*Child Process*/
void		child_one(char *argv, char **ev, int p[2]);

/*Child Two Process*/
void		child_two(char *argv, char **ev, int p[2]);

/*Free handle*/
char		*free_join(char *buffer, char *buff);
void		ft_free_array(char **array);

/*Error handle*/
void		error(const char *s, char *s2);
/*Bonus*/
char		**special_command(char *argv);
//-----

typedef enum e_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_HERE_DOC,
	REDIR_APP,
	REDIR_IN,
	REDIR_OUT,
}			t_type;

// Define a structure to represent tokens
typedef struct s_token
{
	t_type				type;
	struct s_token		*next;
	struct s_token		*prev;
	char				*value;
}			t_token;

typedef struct s_redir
{
	char	*file_name;
	t_type		type;
	int		index;
	struct s_redir	*next;
}			t_redir;

typedef struct s_cmd_table
{
	int					index;
	char				*cmd;
	char				**args;
	char				**exec_args;
	char				*heredoc;
	char				*file_name;
	t_redir				*redir_list;
	struct s_cmd_table	*next;
}			t_cmd_table;

typedef struct s_shell
{
	char			**env;
	int				no_env;
	char			**path;
	char			*line;
	char			*trimmed_line;
	t_token			*tokens;
	t_cmd_table		*cmd_table;
	char			*status_s;
	char			*status_f;
	char			*current_status;
	int				exit_code;
	int				fds[2];
	struct termios	saved;
}			t_shell;

void		xerror(char *s, void *data);

void		ft_free(char **s);
void		fully_free(t_shell *shell);

// shell
void		prepare_prompt(t_shell *shell);
void		empty_env(char **env, t_shell *shell);

// parser
int			ft_parser(t_shell *shell);
t_token		*ft_new_token(char *content, int type);
int			find_token_type(char *line);
int			pipe_counting(char *line);
void		free_tokens(t_token *tokens);
t_cmd_table	*create_table(t_token *tokens, int index);
void		token_print(t_token *tokens);
void		free_cmd_table(t_cmd_table *table);
void		print_cmd_table(t_cmd_table *cmd_table);
t_cmd_table	*prepare_cmd_table(void);
t_cmd_table	*add_to_cmd_table(t_cmd_table *head, t_cmd_table *new_node);
int			count_args(t_token *token);
int			handle_expansions(t_token *tokens, t_shell *shell);
char		*first_redirections(t_token *token);
bool		check_pipe(char *line, int i);
int			num_words(char const *s, char set);
void		remove_quotes_table(t_cmd_table *whole_table);

// parser utils 2
int			is_redirs(t_token *tokens);
int			checker(t_token *tokens, t_type type);
t_redir		*append_token(t_redir *head, t_redir *new_token);
char		**copy_matrix(char **matrix);
char		**no_args(t_cmd_table *table);
char		*custom_trim(char const *s1, char const *set);

//lexer
int			lexer(t_shell *shell);
int			line_valid(t_shell *shell);
int			op_n_pipe(t_shell *shell);
int			check_pipes(t_shell *shell);
int			check_quotes(t_shell *shell);
// lexer utils
int			tilda(t_shell *shell);
int			extra_redirect(t_shell *shell);
int			output_redir(t_shell *shell);
void		syntax_error(char *line);

// lexer utils
int			inp_next_to_out(char *line);
int			check_operator(char *line, char sign);

// executor
void		executor(t_shell *shell);
void		execute_cmd(t_shell *shell);
void		execve_cmd(t_shell *shell);
void		execute_pipes(t_cmd_table *cmd_table, int cmd_count, t_shell *shell);

// handle_redirs
void		handle_redirs(t_redir *redirs);

// builtins
int			ft_env(char **env);
int			exec_builtin(t_shell *shell);
int			is_builtin(char	*cmd);
int			ft_exit(char **args, t_shell *shell);
int			ft_pwd(t_shell *shell);
int			ft_export(char **cmd_args, t_shell *shell);
int			ft_echo(t_shell *shell);
int			ft_cd(char **cmd_args, char **env);
int			ft_unset(char **args, char **env);

// colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"
//SIGNALS
void		check_signals(struct termios *saved);
void		ctrl_c_settings(void);
void		ctrl_slash_settings(void);
void		handle_ctrl_c(int signal, siginfo_t *info, void *x);
void		handle_ctrl_slash(int signal, siginfo_t *info, void *x);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:47 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/16 00:03:25 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
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
# include <time.h>

int	g_ctrl_c;

/* ================================= ERRORS ================================= */
# define BAD_PIPE "Error: syntax error near unexpected token `|'\n"
# define BUILTINS "echo cd pwd export unset env exit history"
# define INVALID_IDEN "!@#$^&*()-+={}[]|;:''<>'',.''/?'"
# define IDENTIFIER " not a valid identifier\n"

/* ================================ VARIABLES ============================== */
# define SQUOTE 39
# define DQUOTE 34
# define SPACES " \t\n\v\r\f"
# define PIPE "|"

/* ================================ PIPEX ================================= */

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
	char				*file_name;
	t_type				type;
	int					index;
	struct s_redir		*next;
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

/* ================================ BUILTINS ================================ */
/* ------------------------------ ft_builtins ------------------------------ */
int			is_builtin(char	*cmd);
int			exec_builtin(t_cmd_table *cmd_table, t_shell *shell, int flag);

/* --------------------------------- ft_cd --------------------------------- */
int			ft_cd(char **cmd_args, char **env);

/* -------------------------------- ft_echo -------------------------------- */
int			ft_echo(char **array);

/* --------------------------------- ft_env --------------------------------- */
int			ft_env(char **env);

/* -------------------------------- ft_exit -------------------------------- */
int			ft_exit(char **args, t_shell *shell);

/* ------------------------------- ft_export ------------------------------- */
char		**ft_add_env(char **env, char *var, int i);
void		export_env(char **env);
int			ft_export(char **cmd_args, t_shell *shell);

/* --------------------------------- ft_pwd --------------------------------- */
int			ft_pwd(t_shell *shell);

/* -------------------------------- ft_unset -------------------------------- */
int			ft_unset(char **args, char **env, int k, int j);
int			special_cmp(const char *s1, const char *s2);

/* ================================ EXECUTOR ================================ */
/* ------------------------------ ft_executor ------------------------------ */
void		executor(t_shell *shell);

/* ---------------------------- ft_handle_redirs ---------------------------- */
void		handle_redirs(t_redir *redirs, int flag, t_shell *shell);

/* ------------------------- ft_multiple_cmds_utils ------------------------- */
void		free_pipes(int **pipes, int cmd_count);
int			**calculate_pipes(int cmd_count);
void		wait_for_pids(int pid, int code, t_shell *shell);
void		count_pipes(int **pipes, int cmd_count, int i);
void		setup_pipes(int i, int **pipes, int cmd_count);

/* ------------------------ ft_multiple_cmds_utils2 ------------------------ */
void		close_pipes(int **pipes, int cmd_count);

/* ---------------------------- ft_multiple_cmds ---------------------------- */
void		execute_pipes(t_cmd_table *cmd_table, int cmd_count,
				t_shell *shell, int code);
void		do_heredocs(t_redir *redir_list, t_shell *shell, int **pipe_fd,
				int cmd_count);
void		handle_m_heredoc(char *heredoc, int *pipe);

/* ----------------------------- ft_single_cmd ----------------------------- */
void		execute_cmd(t_shell *shell);
void		handle_heredoc(char *heredoc, t_shell *shell);
void		execve_cmd(t_shell *shell);

/* =============================== EXPANSIONS =============================== */
/* ------------------------------ ft_expansion ------------------------------ */
void		*replace_with_env(char *type, t_shell *shell);
char		*check_expansion(char *s, int i, t_shell *shell);
char		*make_magic(char *str);

/* --------------------------- ft_expansion_utils --------------------------- */
void		expand_replace_env(char **save, char *type, t_shell *shell);
void		c_inside_join(char **save, char *s, int i);
int			check_inside(char *s, int i);
void		check_flag(char *s, int *flag, int i, int *dq);

/* =============================== FUNCTIONS =============================== */
/* -------------------------------- ft_error -------------------------------- */
void		xerror(char *s, void *data);
void		fd_error(void);

/* -------------------------------- ft_free -------------------------------- */
void		ft_free(char **s);
void		free_redir_list(t_redir *redir_list);
void		fully_free(t_shell *shell);
void		free_when_line_null(t_shell *shell);

/* ---------------------------- ft_signals_child ---------------------------- */
void		ft_signals_child(struct termios *mirror_termios);

/* ------------------------------- ft_signals ------------------------------- */
void		check_signals(struct termios *saved);
void		ctrl_slash_settings(void);
void		ctrl_c_settings(void);
void		handle_ctrl_c(int signal, siginfo_t *info, void *x);
void		sig_int_handler_before_exec(int sig_num);

/* ================================== LEXER ================================= */
/* ----------------------------- ft_lexer_utils ----------------------------- */
int			tilda(t_shell *shell);
int			output_redir(t_shell *shell);
int			input_redir(t_shell *shell);
int			extra_redirect(t_shell *shell);
void		syntax_error(char *line);

/* ---------------------------- ft_lexer_utils2 ---------------------------- */
int			check_operator(char *line, char sign);
int			inp_next_to_out(char *line);
char		*check_home(char **env);

/* -------------------------------- ft_lexer -------------------------------- */
int			lexer(t_shell *shell);

/* ================================= PARSER ================================ */
/* --------------------------- ft_cmd_table_utils --------------------------- */
void		free_cmd_table(t_cmd_table *table);
t_cmd_table	*prepare_cmd_table(void);
t_cmd_table	*add_to_cmd_table(t_cmd_table *head, t_cmd_table *new_node);
int			count_args(t_token *current);
char		*first_redirections(t_token *token);

/* -------------------------- ft_cmd_table_utils2 -------------------------- */
int			is_redirs(t_token *tokens);
int			checker(t_token *tokens, t_type type);
t_redir		*append_redir(t_redir *head, t_redir *new_token);
t_redir		*create_redir(t_token *current, int type);
char		**no_args(t_cmd_table *table);

/* -------------------------- ft_cmd_table_utils3 -------------------------- */
char		*put_cmd(t_token *tokens);

/* ------------------------------ ft_cmd_table ------------------------------ */
t_cmd_table	*create_table(t_token *tokens, int index);
char		**extract_exec_args(t_cmd_table *cmd_table);
char		**extract_args(t_token *tokens, int i, int args_count, char **args);

/* ---------------------------- ft_parser_utils ---------------------------- */
int			pipe_counting(char *line);
int			handle_expansions(t_token *tokens, t_shell *shell);
bool		check_pipe(char *line, int i);
char		**copy_matrix(char **matrix);
int			allocate_args(char ***args, int args_count);

/* ---------------------------- ft_parser_utils2 ---------------------------- */
int			num_words(char const *s, char *set);
int			set_char(char s, const char *set);
char		*custom_trim(char const *s1, char const *set);
t_cmd_table	*create_tokens(char **splitted, int in, t_cmd_table *cmd_table_head,
				t_shell *shell);

/* ------------------------------- ft_parser ------------------------------- */
int			skipping_quotes(char *str, int index);
char		**split_pipes(char *line, char set);
int			skipping_spaces(char *str, int index);
char		**splitter(char *line, char set);
int			ft_parser(t_shell *shell);

/* ------------------------- ft_remove_quotes_utils ------------------------- */
char		*ft_strdup_start_end(char *str, int start, int end);
bool		has_quotes(char *str);
char		*ft_strjoin_char(char *str, char c);
void		remove_quotes_args(char **args);

/* ---------------------------- ft_remove_quotes ---------------------------- */
char		*do_magic(char *str);
void		remove_echo_quotes(char **str);
void		remove_quotes_redir(t_redir *redir_list);
void		remove_quotes_table(t_cmd_table *whole_table);

/* ----------------------------- ft_token_utils ----------------------------- */
t_token		*ft_new_token(char *content, int type);
int			find_token_type(char *line);
void		free_tokens(t_token *tokens);

/* ================================== SHELL ================================= */
/* ------------------------------ ft_empty_env ------------------------------ */
int			check_access(char *argv, char c);
char		*find_path(char **path, char *command);
void		empty_env(char **env, t_shell *shell);

/* ------------------------------- ft_prompt ------------------------------- */
void		check_status(t_shell *shell);
void		prepare_prompt(t_shell *shell);

// colors
# define RESET "\033[0m"
# define BOLD_WHITE "\033[1;37m"
# define ITALIC_WHITE "\033[3;37m"
# define ITALIC_GRAY "\033[3;90m"

/* ================================== MAIN ================================= */
char		**copy_env(char **env);
void		minishell_loop(t_shell *shell);
void		init_shell(t_shell *shell, char **env);

#endif
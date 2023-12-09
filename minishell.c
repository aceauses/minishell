/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/07 20:43:05 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **env)
{
	char	**copied;
	int		y;

	y = 0;
	while (env[y] != NULL)
		y++;
	copied = malloc(sizeof(char *) * (y + 1));
	if (!copied)
		return (NULL);
	y = 0;
	while (env[y] != NULL)
	{
		copied[y] = ft_strdup(env[y]);
		y++;
	}
	copied[y] = NULL;
	return (copied);
}

void	init_data(char **ev, t_shell *shell)
{
	shell->no_env = 0;
	if (!ev[0])
		empty_env(ev, shell);
	shell->env = copy_env(ev);
	if (!shell->env)
		exit(12);
	shell->exit_code = 0;
	shell->saved = (struct termios){0};
	shell->trimmed_line = NULL;
	shell->current_status = NULL;
	shell->status_s = ft_strdup("🟢 ");
	shell->status_f = ft_strdup("🔴 ");
	shell->fds[0] = dup(0);
	shell->fds[1] = dup(1);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argv;
	(void)argc;
	// if (argc > 1)
	// 	xerror("Hey :(", NULL);
	shell = malloc(sizeof(t_shell));
	init_data(env, shell);
	check_signals(&shell->saved);
	while (1)
	{
		prepare_prompt(shell);
		if (isatty(fileno(stdin)))
			shell->line = readline(shell->current_status);
		else
		{
			char	*line;
			line = get_next_line(fileno(stdin));
			if (line == NULL)
			{
				int	code = shell->exit_code;
				// in case of ctrl + D then fully free without trimmed line and cmd_table
				return (code);
			}
			shell->line = ft_strtrim(line, "\n");
			free(line);
		}
		if (shell->line == NULL)
			break ;
		if (ft_strlen(shell->line) == 0)
		{
			free(shell->line);
			continue ;
		}
		add_history(shell->line);
		shell->trimmed_line = ft_strtrim(shell->line, SPACES);
		if (lexer(shell) == 1)
		{
			free(shell->line);
			free(shell->trimmed_line);
			continue ;
		}
		if (ft_parser(shell) == 1)
			continue ;
		executor(shell);
		free(shell->line);
		free(shell->trimmed_line);
		free_cmd_table(shell->cmd_table);
	}
	int	code = shell->exit_code;
	fully_free(shell);
	return (code);
}


/* void	minishell_loop(t_shell *shell)
{
	while (42)
	{
		prepare_prompt(shell);
		check_signals(&shell->saved);
		shell->line = readline(shell->current_status);
		if (shell->line == NULL)
			break ;
		shell->trimmed_line = ft_strtrim(shell->line, SPACES);
		add_history(shell->line);
		if (lexer(shell) == 0 && ft_parser(shell) == 0)
			executor(shell);
		else
			continue ;
	}
}


void	init_shell(t_shell *shell, char **env)
{
	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(12);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	if (argc > 1)
		xerror("Run without any arguments!", NULL);
	else
	{
		init_data(env, &shell);
		init_shell(&shell, env);
		minishell_loop(&shell);
		fully_free(&shell);
	}
}
 */
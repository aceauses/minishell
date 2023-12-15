/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/14 17:29:21 by aceauses         ###   ########.fr       */
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

static void	free_when_line_null(t_shell *shell)
{
	int	code;

	code = 0;
	if (shell->env)
		ft_free(shell->env);
	free(shell->status_f);
	free(shell->status_s);
	free(shell->current_status);
	code = shell->exit_code;
	free(shell);
	rl_clear_history();
	exit(code);
}

void	minishell_loop(t_shell *shell)
{
	check_signals(&shell->saved);
	while (42)
	{
		prepare_prompt(shell);
		if (isatty(fileno(stdin)))
			shell->line = readline(shell->current_status);
		else
		{
			char    *line;
			line = get_next_line(fileno(stdin));
			if (line == NULL)
			{
				free_when_line_null(shell);
				return ;
			}
			shell->line = ft_strtrim(line, "\n");
			free(line);
		}
		if (shell->line == NULL)
			free_when_line_null(shell);
		if (ft_strlen(shell->line) == 0)
		{
			free(shell->line);
			continue ;
		}
		shell->trimmed_line = ft_strtrim(shell->line, SPACES);
		add_history(shell->line);
		if (lexer(shell) == 0 && ft_parser(shell) == 0)
		{
			executor(shell);
			free_cmd_table(shell->cmd_table);
		}
		free(shell->line);
		free(shell->trimmed_line);
	}
}

void	init_shell(t_shell *shell, char **env)
{
	shell->no_env = 0;
	if (!env[0])
		empty_env(env, shell);
	shell->env = copy_env(env);
	if (!shell->env)
		exit(12);
	shell->exit_code = 0;
	shell->saved = (struct termios){0};
	shell->trimmed_line = NULL;
	shell->current_status = NULL;
	shell->cmd_table = NULL;
	shell->status_s = ft_strdup("🟢 ");
	shell->status_f = ft_strdup("🔴 ");
	shell->fds[0] = dup(0);
	shell->fds[1] = dup(1);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argv;
	if (argc > 1)
		xerror("Run without any arguments!", NULL);
	else
	{
		shell = malloc(sizeof(t_shell));
		if (!shell)
			exit(12);
		init_shell(shell, env);
		minishell_loop(shell);
		fully_free(shell);
		return (shell->exit_code);
	}
	return (0);
}
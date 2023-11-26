/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/26 15:54:22 by aceauses         ###   ########.fr       */
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
	if (argc > 1)
		xerror("Hey :(", NULL);
	shell = malloc(sizeof(t_shell));
	init_data(env, shell);
	check_signals(&shell->saved);
	while (1)
	{
		prepare_prompt(shell);
		shell->line = readline(shell->current_status);
		if (shell->line == NULL)
			break ;
		if (ft_strlen(shell->line) == 0)
		{
			free(shell->line);
			continue ;
		}
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
	fully_free(shell);
	return (0);
}

void	fully_free(t_shell *shell)
{

	if (shell->env)
		ft_free(shell->env);
	if (shell->line)
		free(shell->line);
	if (shell->trimmed_line)
		free(shell->trimmed_line);
	if (shell->cmd_table)
	{
		printf("cmd_table free\n");
		free_cmd_table(shell->cmd_table);
	}
	if (shell->current_status)
		free(shell->current_status);
	if (shell->status_f)
		free(shell->status_f);
	if (shell->status_s)
		free(shell->status_s);
	free(shell);
}
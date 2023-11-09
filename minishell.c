/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/09 19:37:44 by aceauses         ###   ########.fr       */
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
	shell->env = copy_env(ev);
	if (!shell->env)
		exit(12);
	shell->status = 0;
	shell->status_s = ft_strdup("🟢 ");
	shell->status_f = ft_strdup("🔴 ");
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	int		builtin;

	(void)argv;
	builtin = 0;
	if (argc > 1)
		xerror("Hey :(", NULL);
	shell = malloc(sizeof(t_shell));
	init_data(env, shell);
	check_signals(&shell->saved);
	while (1)
	{
		// prepare promp for first read or after a command
		prepare_prompt(shell);

		shell->line = readline(shell->current_status);
		if (shell->line == NULL)
			break ;
		// if nothing was written we should skip to next iteration
		if (lexer(shell->line, shell) == 0)
			continue ;
		// Lexer
		// Parser
		// Builtins
		// Executor
		builtin = check_builtins(shell);
		if (builtin == 1)
		{
			free(shell->line);
			free(shell->tokens); // Should make another function to free tokens
			int i = 0;
			while (shell->tokens[i].value != NULL)
				free(shell->tokens[i++].value);
			break ;
		}
		else if (builtin > 1)
		{
			free(shell->line);
			free(shell->tokens); // Should make another function to free tokens
			int i = 0;
			while (shell->tokens[i].value != NULL)
				free(shell->tokens[i++].value);
			continue ;
		}
		// ft_getreq(shell);
		// shell->status = pipex(shell->req, shell->env);
		// ft_free(shell->req);
	}
	ft_free(shell->env);
	// EXIT memory leak
	free(shell->line);
	free(shell->status_s);
	free(shell->status_f);
	free(shell); // free everything inside that was allocated with malloc
	// system("leaks minishell");
	return (0);
}

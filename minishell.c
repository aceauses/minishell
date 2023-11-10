/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/10 15:42:42 by rmitache         ###   ########.fr       */
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
		if (lexer(shell->line, shell) == 1)
			continue ;
		if (check_builtins(shell) == 1)
		{
			int i = 0;
			while (shell->tokens[i].value != NULL)
				free(shell->tokens[i++].value);
			break ;
		}
		else if (check_builtins(shell) > 1)
		{
			free(shell->line);
			free(shell->tokens);
			int i = 0;
			while (shell->tokens[i].value != NULL)
				free(shell->tokens[i++].value);
			continue ;
		}
	}
	fully_free(shell);
	return (0);
}

void	fully_free(t_shell *shell)
{

	if (shell->env)
		ft_free(shell->env);
	if (shell->path)
		ft_free(shell->path);
	if (shell->req)
		ft_free(shell->req);
	// if (shell->line)
	// 	free(shell->line);
	if (shell->tokens)
		free(shell->tokens);
	if (shell->status_f)
		free(shell->status_f);
	if (shell->status_s)
		free(shell->status_s);
}

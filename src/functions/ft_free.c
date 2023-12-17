/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:01:12 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/16 18:55:48 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != NULL)
		free(s[i++]);
	free(s);
}

void	free_redir_list(t_redir *redir_list)
{
	t_redir	*tmp;

	while (redir_list)
	{
		tmp = redir_list;
		redir_list = redir_list->next;
		free(tmp->file_name);
		free(tmp);
	}
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
		free_cmd_table(shell->cmd_table);
	if (shell->current_status)
		free(shell->current_status);
	if (shell->status_f)
		free(shell->status_f);
	if (shell->status_s)
		free(shell->status_s);
	close(shell->fds[0]);
	close(shell->fds[1]);
	rl_clear_history();
	free(shell);
}

void	free_when_line_null(t_shell *shell)
{
	int	code;

	code = 0;
	if (shell->env)
		ft_free(shell->env);
	free(shell->status_f);
	free(shell->status_s);
	free(shell->current_status);
	close(shell->fds[0]);
	close(shell->fds[1]);
	code = shell->exit_code;
	free(shell);
	rl_clear_history();
	exit(code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:22:18 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/07 21:42:00 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_counting(t_cmd_table *cmd_table)
{
	int			i;
	t_cmd_table	*tmp;

	i = 0;
	tmp = cmd_table;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	executor(t_shell *shell)
{
	int		cmd_count;

	cmd_count = cmd_counting(shell->cmd_table);
	if (cmd_count == 1)
	{
		if (is_builtin(shell->cmd_table->cmd))
		{
			handle_redirs(shell->cmd_table->redir_list);
			shell->exit_code = exec_builtin(shell);
			dup2(shell->fds[0], STDIN_FILENO);
			dup2(shell->fds[1], STDOUT_FILENO);
		}
		else
			execute_cmd(shell);
	}
	else
		execute_pipes(shell->cmd_table, cmd_count, shell);
}

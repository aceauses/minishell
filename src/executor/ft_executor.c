/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:22:18 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/20 20:23:57 by aceauses         ###   ########.fr       */
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
	// t_cmd_table	*cmd_table;
	int			cmd_count;

	// cmd_table = shell->cmd_table;
	cmd_count = cmd_counting(shell->cmd_table);
	// printf("cmd_count: %d\n", cmd_count);
	if (cmd_count == 1)
	{
		if (is_builtin(shell->cmd_table->cmd))
			shell->exit_code = exec_builtin(shell);
		else
			execute_cmd(shell);
	}
	else
		printf("Doesnt work with multiple yet\n");
		// execute_pipes(shell->cmd_table);
}

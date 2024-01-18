/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:22:18 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/16 23:28:10 by aceauses         ###   ########.fr       */
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

static	int	should_run_child(t_shell *shell)
{
	if (ft_strcmp(shell->cmd_table->cmd, "cd") == 0
		|| ft_strcmp(shell->cmd_table->cmd, "export") == 0
		|| ft_strcmp(shell->cmd_table->cmd, "unset") == 0
		|| ft_strcmp(shell->cmd_table->cmd, "env") == 0
		|| ft_strcmp(shell->cmd_table->cmd, "pwd") == 0
		|| ft_strcmp(shell->cmd_table->cmd, "echo") == 0)
	{
		shell->exit_code = exec_builtin(shell->cmd_table, shell, 0);
		return (1);
	}
	return (0);
}

static void	execute_in_child(t_shell *shell)
{
	handle_redirs(shell->cmd_table->redir_list, 0, shell);
	shell->exit_code = exec_builtin(shell->cmd_table, shell, 1);
	dup2(shell->fds[0], STDIN_FILENO);
	dup2(shell->fds[1], STDOUT_FILENO);
	close(shell->fds[0]);
	close(shell->fds[1]);
	exit(shell->exit_code);
}

static void	execute_single_builtin(t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (should_run_child(shell))
		return ;
	pid = fork();
	if (pid == -1)
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
	else if (pid == 0)
	{
		ft_signals_child(&shell->saved);
		execute_in_child(shell);
	}
	else
	{
		waitpid(pid, &status, 0);
		shell->exit_code = WEXITSTATUS(status);
		if (ft_strcmp(shell->cmd_table->cmd, "exit") == 0)
			ft_exit(shell->cmd_table->exec_args, shell);
	}
}

void	executor(t_shell *shell)
{
	int		cmd_count;
	int		norm_i;

	norm_i = 0;
	cmd_count = cmd_counting(shell->cmd_table);
	if (cmd_count == 1)
	{
		if (is_builtin(shell->cmd_table->cmd))
			execute_single_builtin(shell);
		else
			execute_cmd(shell);
	}
	else
		execute_pipes(shell->cmd_table, cmd_count, shell, norm_i);
}

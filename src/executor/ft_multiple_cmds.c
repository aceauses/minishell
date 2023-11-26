/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:52:20 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/26 16:03:58 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(int pipes[][2], int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	exec_bin(t_cmd_table *cmd_table, t_shell *shell)
{
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	path = NULL;
	cmd = ft_strtrim(cmd_table->cmd, " ");
	if (cmd == NULL)
		exit(0);
	if (check_access(cmd, 'X') < 0)
		path = find_path(shell->env, cmd);
	else
		path = ft_strdup(cmd);
	if (path)
	{
		execve(path, cmd_table->exec_args, shell->env);
		free(path);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	fully_free(shell);
	exit(127);
}

static void	exec_cmd(t_cmd_table *cmd_table, t_shell *shell)
{
	handle_redirs(cmd_table->redir_list);
	if (is_builtin(cmd_table->cmd))
		shell->exit_code = exec_builtin(shell);
	else
		exec_bin(cmd_table, shell);
}

void	execute_pipes(t_cmd_table *cmd_table, int cmd_count, t_shell *shell)
{
	int	i;
	int	pipes[cmd_count - 1][2];
	int	pid;

	i = 0;
	while (i < cmd_count - 1)
	{
		pipe(pipes[i]);
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i != cmd_count - 1)
				dup2(pipes[i][1], STDOUT_FILENO);
			close_pipes(pipes, cmd_count);
			exec_cmd(cmd_table, shell);
		}
		cmd_table = cmd_table->next;
		i++;
	}
	close_pipes(pipes, cmd_count);
	waitpid(pid, &shell->exit_code, 0);
}
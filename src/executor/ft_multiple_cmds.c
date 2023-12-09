/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:52:20 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/09 15:30:19 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(int **pipes, int cmd_count)
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

static void	handle_m_heredoc(char *heredoc, t_shell *shell)
{
	int		fd;
	char	*line;

	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		fd_error();
	dup2(shell->fds[0], STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, heredoc) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
		fd_error();
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	exec_bin(t_cmd_table *cmd_table, t_shell *shell)
{
	char	*path;
	char	*cmd;

	path = NULL;
	if (cmd_table->cmd == NULL)
		exit(0);
	cmd = ft_strtrim(cmd_table->cmd, " ");
	if (check_access(cmd, 'X') < 0)
		path = find_path(shell->env, cmd);
	else
		path = ft_strdup(cmd);
	if (path == NULL || ft_strlen(cmd) == 0)
	{
		ft_dprintf(2, "minishell: %s: command not found\n", cmd);
		free(path);
		fully_free(shell);
		exit(127);
	}
	if (execve(path, cmd_table->exec_args, shell->env) == -1)
	{
		ft_dprintf(2, "minishell: %s: %s\n", cmd, strerror(errno));
		free(path);
		fully_free(shell);
		exit(errno);
	}
}

static void	exec_cmd(t_cmd_table *cmd_table, t_shell *shell)
{
	handle_redirs(cmd_table->redir_list);
	if (cmd_table->heredoc != NULL)
		handle_m_heredoc(cmd_table->heredoc, shell);
	if (is_builtin(cmd_table->cmd))
	{
		shell->exit_code = exec_builtin(shell);
		exit(shell->exit_code);
	}
	else
		exec_bin(cmd_table, shell);
}

void	execute_pipes(t_cmd_table *cmd_table, int cmd_count, t_shell *shell)
{
	int	i;
	int	**pipes;
	int	pid;
	int	code;

	i = -1;
	code = 0;
	pipes = calculate_pipes(cmd_count);
	if (pipes == NULL)
		return ;
	count_pipes(pipes, cmd_count, i);
	while (++i < cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			setup_pipes(i, pipes, cmd_count);
			close_pipes(pipes, cmd_count);
			exec_cmd(cmd_table, shell);
		}
		cmd_table = cmd_table->next;
	}
	close_pipes(pipes, cmd_count);
	wait_for_pids(pid, code, shell);
	free_pipes(pipes, cmd_count);
}

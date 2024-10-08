/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:52:20 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/17 16:47:06 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_m_heredoc(char *heredoc, int *pipe, t_shell *shell)
{
	int		fd;
	char	*line;

	fd = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		fd_error();
	g_ctrl_c = 0;
	while (1 && g_ctrl_c == 0)
	{
		line = readline("> ");
		if (ft_strcmp(line, heredoc) == 0 || !line || g_ctrl_c == 1)
		{
			free(line);
			g_ctrl_c = 0;
			break ;
		}
		if (ft_strchr(line, '$') != NULL)
			line = check_expansion(line, -1, shell);
		ft_dprintf(fd, "%s\n", line);
		if (line != NULL)
			free(line);
	}
	close(fd);
	open_close_fd(fd, pipe, heredoc);
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
	handle_redirs(cmd_table->redir_list, 1, shell);
	if (is_builtin(cmd_table->cmd))
	{
		shell->exit_code = exec_builtin(cmd_table, shell, 0);
		exit(shell->exit_code);
	}
	else
		exec_bin(cmd_table, shell);
}

void	do_heredocs(t_redir *redir_list, t_shell *shell, int **pipe_fd,
		int cmd_count)
{
	int	i;

	i = 0;
	(void)shell;
	while (i < cmd_count)
	{
		if (redir_list)
		{
			if (redir_list->type == TOKEN_HERE_DOC)
				handle_m_heredoc(redir_list->file_name, pipe_fd[i], shell);
			redir_list = redir_list->next;
		}
		i++;
	}
}

void	execute_pipes(t_cmd_table *cmd_table, int cmd_count,
		t_shell *shell, int code)
{
	int		i;
	int		**pipes;
	pid_t	pid;

	i = -1;
	pipes = calculate_pipes(cmd_count);
	if (pipes == NULL)
		return ;
	count_pipes(pipes, cmd_count, i);
	while (++i < cmd_count)
	{
		do_heredocs(cmd_table->redir_list, shell, pipes, cmd_count);
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

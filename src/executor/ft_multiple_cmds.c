/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:52:20 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/15 20:18:52 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_ctrl_c = 0;

void	sig_int_handler_before_exec(int sig_num)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_ctrl_c = 1;
	(void)sig_num;
}

void	handle_m_heredoc(char *heredoc, t_shell *shell, int *pipe)
{
	int		fd;
	char	*line;

	fd = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		fd_error();
	(void)shell;
	while (1 && g_ctrl_c == 0)
	{
		signal(SIGINT, sig_int_handler_before_exec);
		line = readline("> ");
		if (ft_strcmp(line, heredoc) == 0 || !line || g_ctrl_c == 1)
		{
			free(line);
			break ;
		}
		ft_dprintf(fd, "%s\n", line);
		free(line);
	}
	g_ctrl_c = 0;
	close(fd);
	fd = open(heredoc, O_RDONLY);
	if (fd == -1)
		fd_error();
	dup2(fd, pipe[0]);
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
	while (i < cmd_count)
	{
		if (redir_list)
		{
			if (redir_list->type == TOKEN_HERE_DOC)
				handle_m_heredoc(redir_list->file_name, shell, pipe_fd[i]);
			redir_list = redir_list->next;
		}
		i++;
	}
}

void	execute_pipes(t_cmd_table *cmd_table, int cmd_count,
		t_shell *shell, int code)
{
	int	i;
	int	**pipes;
	int	pid;

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

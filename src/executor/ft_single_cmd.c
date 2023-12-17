/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_single_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:46:43 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/17 13:19:14 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execve_cmd_error(t_shell *shell, char *cmd_place)
{
	ft_dprintf(2, "minishell: %s: %s\n", shell->cmd_table->cmd,
		strerror(errno));
	free(cmd_place);
	fully_free(shell);
	exit(errno);
}

static void	cmd_not_found(t_shell *shell, char *cmd_place)
{
	ft_dprintf(2, "minishell: %s: command not found\n", shell->cmd_table->cmd,
		strerror(errno));
	free(cmd_place);
	fully_free(shell);
	exit(127);
}

void	execve_cmd(t_shell *shell)
{
	char	*cmd_place;

	cmd_place = NULL;
	if (shell->cmd_table->cmd == NULL)
		exit(0);
	if (check_access(shell->cmd_table->cmd, 'X') < 0)
		cmd_place = find_path(shell->env, shell->cmd_table->cmd);
	else
		cmd_place = ft_strdup(shell->cmd_table->cmd);
	if (cmd_place == NULL || !ft_strlen(shell->cmd_table->cmd)
		|| (!ft_strncmp(shell->cmd_table->cmd, "..", 2)
			&& ft_strlen(shell->cmd_table->cmd) == 2)
		|| (!ft_strncmp(shell->cmd_table->cmd, ".", 1)
			&& ft_strlen(shell->cmd_table->cmd) == 1))
		cmd_not_found(shell, cmd_place);
	if (execve(cmd_place, shell->cmd_table->exec_args, shell->env) == -1)
		execve_cmd_error(shell, cmd_place);
}

void	handle_heredoc(char *heredoc, t_shell *shell)
{
	int		fd;
	char	*line;

	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		fd_error();
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, heredoc) == 0)
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$'))
			line = check_expansion(line, -1, shell);
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

/**
 * @brief Executes a single command.
 * 
 * @param shell 
 */
void	execute_cmd(t_shell *shell)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_dprintf(2, "minishell: fork: %s\n", strerror(errno));
	else if (pid == 0)
	{
		ft_signals_child(&shell->saved);
		handle_redirs(shell->cmd_table->redir_list, 0, shell);
		execve_cmd(shell);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_single_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:46:43 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/26 15:26:28 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (cmd_place == NULL)
	{
		printf("minishell: %s: command not found\n", shell->cmd_table->cmd);
		fully_free(shell);
		exit(127);
	}
	if (execve(cmd_place, shell->cmd_table->exec_args, shell->env) == -1)
	{
		printf("minishell: %s: %s\n", shell->cmd_table->cmd, strerror(errno));
		free_cmd_table(shell->cmd_table);
		exit(1);
	}
}

static void	handle_heredoc(char *heredoc)
{
	int		fd;
	char	*line;

	if (heredoc == NULL)
		return ;
	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("minishell: %s\n", strerror(errno));
		exit(1);
	}
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
	{
		printf("minishell: %s\n", strerror(errno));
		exit(1);
	}
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
	{
		printf("minishell: fork: %s\n", strerror(errno));
		exit(1);
	}
	else if (pid == 0)
	{
		handle_redirs(shell->cmd_table->redir_list);
		handle_heredoc(shell->cmd_table->heredoc);
		execve_cmd(shell);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_cmds_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:36:35 by rmitache          #+#    #+#             */
/*   Updated: 2023/12/11 02:59:25 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(int **pipes, int cmd_count)
{
	int	i;

	i = -1;
	while (++i < cmd_count - 1)
		free(pipes[i]);
	free(pipes);
}

int	**calculate_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (pipes == NULL)
		return (NULL);
	while (++i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
			return (NULL);
	}
	return (pipes);
}

void	wait_for_pids(int pid, int code, t_shell *shell)
{
	waitpid(pid, &code, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(code))
		shell->exit_code = WEXITSTATUS(code);
}

void	count_pipes(int **pipes, int cmd_count, int i)
{
	while (++i < cmd_count - 1)
		pipe(pipes[i]);
	i = -1;
}

void	setup_pipes(int i, int **pipes, int cmd_count)
{
	if (i != 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i != cmd_count - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
}

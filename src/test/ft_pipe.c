/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:35:20 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/03 15:37:24 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Child Process should read from infile and execute the command*/
void	child_one(char *argv, char **ev, int p[2])
{
	char	**command;
	char	*path;

	if (ft_strncmp(argv, "awk", 3) == 0
		|| ft_strncmp(argv, "sed", 3) == 0)
		command = special_command(argv);
	else
		command = ft_split(argv, ' ');
	if (check_access(command[0], 'X') < 0)
		path = find_path(ev, command[0]);
	else
		path = command[0];
	if (command[0] == NULL || !path)
		error("command not found", command[0]);
	close(p[0]);
	dup2(p[1], 1);
	close(p[1]);
	if (execve(path, command, ev) == -1)
		error("Executing first command", command[0]);
}

void	child_two(char *argv, char **ev, int p[2])
{
	char	**command;
	char	*path;

	if (ft_strncmp(argv, "awk", 3) == 0
		|| ft_strncmp(argv, "sed", 3) == 0)
		command = special_command(argv);
	else
		command = ft_split(argv, ' ');
	if (check_access(command[0], 'X') < 0)
		path = find_path(ev, command[0]);
	else
		path = command[0];
	if (!command[0] || !path)
		error("command not found", command[0]);
	// close(p[1]);
	// dup2(fd, 1);
	// close(fd);
	dup2(p[0], 0);
	close(p[0]);
	if (execve(path, command, ev) == -1)
		error("Executing Second command", NULL);
}

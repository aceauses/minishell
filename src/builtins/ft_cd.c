/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:44:29 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/05 16:51:45 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arguments(char **cmd_args, char *path)
{
	if (cmd_args[1] == NULL && path == NULL)
		return (ft_dprintf(2, "minishell: cd: HOME not set\n"), 1);
	if (cmd_args[1] == NULL && path != NULL)
		chdir(path);
	else if (ft_strncmp(cmd_args[1], "~", 1) == 0 && path != NULL)
	{
		path = free_join(path, cmd_args[1] + 1);
		if (chdir(path) == -1)
		{
			ft_dprintf(2, "minishell: cd: %s: No such file or directory\n",
				path);
			return (free(path), 1);
		}
	}
	else if (chdir(cmd_args[1]) == -1)
	{
		ft_dprintf(2, "minishell: cd: %s: No such file or directory\n",
			cmd_args[1]);
		return (free(path), 1);
	}
	return (free(path), 0);
}

int	ft_cd(char **cmd_args, char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	if (check_arguments(cmd_args, path) == 1)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:44:29 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:20 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **cmd_args, char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	if (cmd_args[1] == NULL)
		chdir(path);
	else if (ft_strncmp(cmd_args[1], "~", 1) == 0)
	{
		path = ft_strjoin(path, cmd_args[1] + 1);
		if (chdir(path) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(cmd_args[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (free(path), 1);
		}
	}
	else if (chdir(cmd_args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd_args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (free(path), 1);
	}
	return (free(path), 0);
}

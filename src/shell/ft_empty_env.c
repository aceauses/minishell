/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:27:40 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/15 23:28:37 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(char *argv, char c)
{
	int	re;

	re = -1;
	if (c == 'R')
		re = access((const char *)argv, R_OK);
	else if (c == 'W')
		re = access((const char *)argv, W_OK);
	else if (c == 'X')
		re = access((const char *)argv, X_OK);
	else
		printf("Please give a valid instruction.\n");
	return (re);
}

static void	remove_and_put(char **s, int i, char *command)
{
	char	*temp;

	temp = ft_strdup(s[i]);
	free(s[i]);
	s[i] = ft_strtrim(temp, "PATH=");
	free(temp);
	s[i] = free_join(s[i], "/");
	s[i] = free_join(s[i], command);
}

char	*find_path(char **path, char *command)
{
	char	**paths;
	char	*save;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (path[j] != NULL && ft_strncmp(path[j], "PATH=", 5) != 0)
		j++;
	paths = ft_split(path[j], ':');
	if (!paths)
		return (NULL);
	if (!command || command[0] == '.' || command[0] == '/')
		return (ft_free(paths), NULL);
	save = NULL;
	while (paths[i] != NULL)
	{
		remove_and_put(paths, i, command);
		if (check_access(paths[i], 'X') != -1)
			break ;
		i++;
	}
	if (paths[i] == NULL && check_access(paths[i - 1], 'X') == -1)
		return (ft_free(paths), paths = NULL, NULL);
	return (save = ft_strdup(paths[i]), ft_free(paths), save);
}

void	empty_env(char **env, t_shell *shell)
{
	char	*current_path;

	shell->no_env = 1;
	current_path = NULL;
	current_path = getcwd(current_path, sizeof((int *)100));
	env[0] = ft_strdup("USER=minishell");
	env[1] = ft_strjoin("PWD=", current_path);
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	env[5] = ft_strdup("TERM=xterm-256color");
	env[6] = NULL;
	free(current_path);
}

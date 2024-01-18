/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:44:29 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/15 16:24:55 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	change_env(char **env, char *var, char *value)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] != NULL)
	{
		if (special_cmp(var, env[i]) == 0)
		{
			free(env[i]);
			tmp = ft_strjoin(var, "=");
			env[i] = ft_strjoin(tmp, value);
			free(tmp);
			return ;
		}
		i++;
	}
	return ;
}

static	int	ft_chdir(char *path, char **env)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		ft_dprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (free(oldpwd), -1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_dprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (free(oldpwd), -1);
	}
	change_env(env, "PWD", pwd);
	change_env(env, "OLDPWD", oldpwd);
	return (free(pwd), free(oldpwd), 0);
}

static int	check_arguments(char **cmd_args, char *path, char *old, char **env)
{
	if (cmd_args[1] == NULL && path == NULL)
		return (ft_dprintf(2, "minishell: cd: HOME not set\n"), 1);
	if (cmd_args[1] == NULL && path != NULL)
		ft_chdir(path, env);
	else if (ft_strncmp(cmd_args[1], "~", 1) == 0 && path != NULL)
	{
		path = free_join(path, cmd_args[1] + 1);
		if (ft_chdir(path, env) == -1)
			return (free(path), free(old), 1);
	}
	else if (ft_strncmp(cmd_args[1], "-", 1) == 0 && old != NULL)
	{
		old = free_join(old, cmd_args[1] + 1);
		if (ft_chdir(old, env) == -1)
			return (free(path), free(old), 1);
	}
	else if (ft_chdir(cmd_args[1], env) == -1)
		return (free(path), free(old), 1);
	return (free(path), free(old), 0);
}

int	ft_cd(char **cmd_args, char **env)
{
	int		i;
	char	*path;
	char	*oldpwd;

	i = 0;
	path = NULL;
	oldpwd = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			path = ft_strdup(env[i] + 5);
		if (ft_strncmp(env[i], "OLDPWD==", 7) == 0)
			oldpwd = ft_strdup(env[i] + 7);
		i++;
	}
	if (check_arguments(cmd_args, path, oldpwd, env) == 1)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:45:35 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/15 20:54:46 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '=' && i == 0)
		return (0);
	if (str[i] == '\0')
		return (2);
	return (1);
}

static void	check_env_flag(int flag, char **new_env, char *var, int i)
{
	if (flag == 0)
		new_env[i] = ft_strdup(var);
	if (flag == 0)
		new_env[i + 1] = NULL;
	else
		new_env[i] = NULL;
}

char	**ft_add_env(char **env, char *var, int i)
{
	int		flag;
	char	**splitted;
	char	**new_env;

	while (env && env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (new_env == NULL)
		return (NULL);
	i = -1;
	flag = 0;
	splitted = ft_split(var, '=');
	while (env[++i] != NULL)
	{
		if (special_cmp(splitted[0], env[i]) == 0)
		{
			new_env[i] = ft_strdup(var);
			flag = 1;
		}
		else
			new_env[i] = ft_strdup(env[i]);
	}
	check_env_flag(flag, new_env, var, i);
	return (ft_free(env), ft_free(splitted), new_env);
}

void	export_env(char **env)
{
	int	i;

	i = -1;
	while (env && env[++i] != NULL)
		printf("declare -x %s\n", env[i]);
}

int	ft_export(char **cmd_args, t_shell *shell)
{
	int		i;
	int		norm_i;
	char	*var;

	i = 1;
	norm_i = 0;
	if (cmd_args[1] == NULL)
		return (export_env(shell->env), 0);
	while (cmd_args[i] != NULL)
	{
		if (is_valid(cmd_args[i]) == 1)
		{
			var = ft_strdup(cmd_args[i]);
			shell->env = ft_add_env(shell->env, var, norm_i);
			free(var);
		}
		else if (is_valid(cmd_args[i]) == 2 && cmd_args[i + 1] == NULL)
			return (0);
		else if (is_valid(cmd_args[i]) == 0)
			return (ft_dprintf(2, "minishell: export: `%s':" IDENTIFIER,
					cmd_args[i]), 1);
		i++;
	}
	return (0);
}

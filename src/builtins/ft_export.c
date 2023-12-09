/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:45:35 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/05 16:54:07 by rmitache         ###   ########.fr       */
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

char	**ft_add_env(char **env, char *var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env && env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	return (ft_free(env), new_env);
}

void	export_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

int	ft_export(char **cmd_args, t_shell *shell)
{
	int		i;
	char	*var;

	i = 1;
	if (cmd_args[1] == NULL)
		return (export_env(shell->env), 0);
	while (cmd_args[i] != NULL)
	{
		if (is_valid(cmd_args[i]) == 1)
		{
			var = ft_strdup(cmd_args[i]);
			// if (replace_in_env(var, shell->env))
			// 	shell->env = ft_replace_env(shell->env, var);
			// else
				shell->env = ft_add_env(shell->env, var);
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

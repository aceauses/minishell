/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:45:35 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/27 10:40:24 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '=' && str[i + 1] != '\0' && str[i + 1] != '=')
			i++;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	**ft_add_env(char **env, char *var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i] != NULL)
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

int	ft_export(char **cmd_args, t_shell *shell)
{
	int		i;
	char	*var;

	i = 1;
	if (cmd_args[1] == NULL)
	{
		return (0);
	}
	while (cmd_args[i] != NULL)
	{
		if (is_valid(cmd_args[i]))
		{
			var = ft_strdup(cmd_args[i]);
			shell->env = ft_add_env(shell->env, var);
			free(var);
		}
		else
			ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n",
				cmd_args[i]);
		i++;
	}
	return (0);
}

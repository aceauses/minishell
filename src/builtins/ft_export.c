/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:45:35 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/04 20:11:55 by aceauses         ###   ########.fr       */
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
		if (str[i] == '=' || !ft_isalnum(str[i]))
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
	return (new_env);
}

int	ft_export(t_shell *shell)
{
	char	**var;

	if (ft_strncmp(shell->line, "export", 6) != 0)
		return (0);
	var = ft_split(shell->line, ' ');
	if (var[1] == NULL)
	{
		ft_putstr_fd("export: not enough arguments\n", 2);
		return (0);
	}
	if (!is_valid(var[1]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(var[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	shell->env = ft_add_env(shell->env, var[1]);
	return (1);
}
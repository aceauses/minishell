/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:23:51 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/01 18:58:04 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_cmp(const char *s1, const char *s2)
{
	if ((!s1 && !s2) || (!s1 && s2) || (s1 && !s2))
		return (1);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if (*s2 == '=' && *s1 == '\0')
		return (0);
	if (*s1 != *s2)
		return (1);
	return (0);
}

int	ft_unset(char **args, char **env)
{
	int	i;
	int	k;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (env[j])
		{
			if (special_cmp(args[i], env[j]) == 0)
			{
				free(env[j]);
				k = j - 1;
				while (++k && env[k + 1] != NULL)
					env[k] = env[k + 1];
				env[k] = NULL;
				break ;
			}
			else if (env[j + 1] == NULL)
				return (ft_dprintf(2, "minishell: unset: `%s': not a valid identifier\n", args[i]), 1);
			j++;
		}
		i++;
	}
	return (0);
}

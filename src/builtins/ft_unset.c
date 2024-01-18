/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:23:51 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/09 14:32:12 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_cmp(const char *s1, const char *s2)
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

static int	set_char_unset(char *s, const char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (set[i])
	{
		j = 0;
		while (s[j])
		{
			if (set[i] == s[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **args, char **env, int k, int j)
{
	int	i;

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
			else if (set_char_unset(args[i], INVALID_IDEN) == 1)
				return (ft_dprintf(2, "minishell: unset: `%s':"IDENTIFIER,
						args[i]), 1);
			j++;
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:12:44 by rmitache          #+#    #+#             */
/*   Updated: 2023/12/01 15:37:54 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_operator(char *line, char sign)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == sign)
		{
			i++;
			while (line[i] == ' ' && line[i] != '\0')
				i++;
			if (line[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	inp_next_to_out(char *line)
{
	int	l;

	l = ft_strlen(line);
	if (ft_strnstr(line, "<>", l) || ft_strnstr(line, "><", l))
		return (1);
	return (0);
}

char	*check_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:12:44 by rmitache          #+#    #+#             */
/*   Updated: 2023/11/28 12:18:01 by rmitache         ###   ########.fr       */
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
		if (env[i][0] == 'H' && env[i][1] == 'O' && env[i][2] == 'M'
			&& env[i][3] == 'E' && env[i][4] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}

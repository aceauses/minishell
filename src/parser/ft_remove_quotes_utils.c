/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:59:21 by rmitache          #+#    #+#             */
/*   Updated: 2023/12/16 12:13:43 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_start_end(char *str, int start, int end)
{
	int		i;
	char	*memory;

	if (str == NULL || start < 0 || end < start)
		return (NULL);
	memory = (char *)malloc(end - start + 1);
	if (memory == NULL)
		return (NULL);
	i = -1;
	while (start + ++i < end)
		memory[i] = str[start + i];
	memory[i] = '\0';
	return (memory);
}

bool	has_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
	}
	return (0);
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*res;
	int		i;

	if (str == NULL)
	{
		res = (char *)malloc(2);
		if (res == NULL)
			return (NULL);
		res[0] = c;
		res[1] = '\0';
		return (res);
	}
	res = (char *)malloc(ft_strlen(str) + 2);
	if (res == NULL)
		return (NULL);
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i++] = c;
	res[i] = '\0';
	free(str);
	return (res);
}

void	remove_quotes_args(char **args)
{
	int		i;
	char	*tmp;

	i = -1;
	while (args && args[++i] != NULL)
	{
		tmp = do_magic(args[i]);
		free(args[i]);
		args[i] = tmp;
	}
}

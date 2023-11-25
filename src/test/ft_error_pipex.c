/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:59 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/19 17:22:29 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(const char *s, char *s2)
{
	ft_putstr_fd("pipex: ", 2);
	if (s2)
	{
		s2 = free_join(s2, ": ");
		ft_putstr_fd(s2, 2);
		free(s2);
	}
	if (!ft_strncmp(s, "command not found", 18))
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	perror(s);
	exit(EXIT_FAILURE);
}

char	*free_join(char *buffer, char *buff)
{
	char	*temp;

	temp = ft_strjoin(buffer, buff);
	free(buffer);
	return (temp);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

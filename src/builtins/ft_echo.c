/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:24:51 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/04 18:15:31 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_n(char *array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	if (ft_strcmp(array, "-n") == 0)
		return (1);
	while (array[i] != '\0')
	{
		if (array[i] == '-')
		{
			i++;
			while (array[i] == 'n')
			{
				i++;
				if (array[i] == '\0')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_echo(char **array)
{
	int		i;
	int		flag;

	i = 1;
	flag = check_for_n(array[1]);
	if (flag == 1)
		i++;
	while (array[i] != NULL)
	{
		if (ft_strcmp(array[i], "-n") != 0 || (i >= 2 && array[i + 1] == NULL))
		{
			printf("%s", array[i]);
			if (array[i + 1] != NULL)
				printf(" ");
		}
		i++;
	}
	if (flag != 1)
		printf("\n");
	return (0);
}

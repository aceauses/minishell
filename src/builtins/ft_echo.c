/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:24:51 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/28 12:46:49 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	n_args(char **args)
{
	int i;
	
	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

int		ft_echo(t_shell *shell)
{
	char	**args;
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	args = ft_split(shell->line, ' ');
	if (ft_strncmp(args[0], "echo", 5) != 0)
		return (0);
	if (n_args(args) > 1)
	{
		if ((ft_strncmp(args[i], "-n", 2) == 0))
			n_flag = i++;
		while (args[i] != NULL)
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] != NULL)
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	ft_free(args);
	return (1);
}

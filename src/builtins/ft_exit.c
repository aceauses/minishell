/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:04:40 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/28 15:12:55 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_exit_code(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0 || arg[i] == ' ')
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", arg);
			exit(255);
		}
		i++;
	}
	if (i == 0)
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", arg);
		exit(255);
	}
}

int	ft_exit(char **args, t_shell *shell)
{
	int	code;

	if (args[1] == NULL)
	{
		fully_free(shell);
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	else if (args[1] != NULL)
	{
		check_exit_code(args[1]);
		code = ft_atoi(args[1]);
		fully_free(shell);
		ft_putstr_fd("exit\n", 2);
		exit(code);
	}
	else
		return (ft_dprintf(2, "minishell: exit: too many arguments\n"), 1);
	return (0);
}

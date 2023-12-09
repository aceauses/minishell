/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:04:40 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/05 13:09:31 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_sign(char *arg)
{
	int	amount;
	int	problem;
	int	i;

	i = 0;
	amount = 0;
	problem = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0 && arg[i] != '+' && arg[i] != '-')
			problem = 1;
		if (arg[i] == '+' || arg[i] == '-')
			amount++;
		i++;
	}
	if (amount > 1 || problem == 1)
		return (1);
	return (0);
}

static int	check_exit_code(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0 && check_for_sign(arg))
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
				arg);
			exit(255);
		}
		if (arg[i] == '-' && ft_isdigit(arg[i + 1]))
			return (1);
		i++;
	}
	if (i == 0)
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", arg);
		exit(255);
	}
	return (0);
}

static	void	exit_with_minus(char *arg, t_shell *shell)
{
	int	code;

	code = ft_atoi(arg);
	fully_free(shell);
	ft_putstr_fd("exit\n", 2);
	exit(code - 256);
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
		if (check_exit_code(args[1]) == 1)
			exit_with_minus(args[1], shell);
		else
		{
			code = ft_atoi(args[1]);
			fully_free(shell);
			ft_putstr_fd("exit\n", 2);
			exit(code);
		}
	}
	else
		return (ft_dprintf(2, "minishell: exit: too many arguments\n"), 1);
	return (0);
}

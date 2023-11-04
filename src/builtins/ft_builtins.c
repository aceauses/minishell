/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:08:45 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/04 20:06:37 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_shell *shell)
{
	if (check_exit(shell->line))
		return (1);
	if (env_print(shell) || pwd_print(shell) || ft_export(shell))
		return (2);
	return (0);
}

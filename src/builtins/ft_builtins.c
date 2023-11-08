/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:08:45 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/07 17:51:13 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_shell *shell)
{
	if (check_exit(shell->line))
		return (1);
	// if (env_print(shell) || pwd_print(shell) || ft_export(shell)
	// 	||  (shell))
		// return (2);
	return (0);
}

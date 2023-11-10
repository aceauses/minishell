/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:08:45 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/10 14:30:01 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_shell *shell)
{
	if (check_exit(shell->line) == 1)
		return (1);
	// if (env_print(shell) || pwd_print(shell) || ft_export(shell)
	// 	||  (shell))
		// return (2);
	return (0);
}
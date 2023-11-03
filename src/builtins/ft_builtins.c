/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:08:45 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/03 17:55:58 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char *line, t_shell *shell)
{
	if (check_exit(line))
		return (1);
	if (env_print(line, shell) || pwd_print(line, shell))
		return (2);
	return (0);
}

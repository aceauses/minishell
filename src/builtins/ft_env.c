/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:04:03 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/04 19:56:45 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_print(t_shell *shell)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (shell->line[i] == ' ')
		i++;
	if (shell->line[i] == 'e' && shell->line[i + 1] == 'n' && shell->line[i + 2] == 'v')
	{
		while (shell->env[k] != NULL && shell->env)
		{
			printf("%s\n", shell->env[k]);
			k++;
		}
	}
	else
		return (0);
	return (1);
}

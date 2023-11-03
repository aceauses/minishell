/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:52:59 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/03 18:04:23 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_print(char *line, t_shell *shell)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'p' && line[i + 1] == 'w' && line[i + 2] == 'd')
	{
		if (shell->env[0] == NULL)
			return (1);
		while (ft_strncmp(shell->env[k], "PWD=", 4) != 0 && shell->env[k] != NULL)
			k++;
		printf("%s\n", shell->env[k] + 4);
		return (1);
	}
	return (0);
}

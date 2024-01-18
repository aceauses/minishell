/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:52:59 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/15 16:45:20 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	k = 0;
	tmp = getcwd(NULL, 0);
	while (shell->env[k] != NULL && ft_strncmp(shell->env[k], "PWD=", 4) != 0)
		k++;
	if (shell->env[k] == NULL)
		printf("%s\n", tmp);
	else
		printf("%s\n", shell->env[k] + 4);
	return (free(tmp), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:27:40 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/16 18:34:29 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty_env(char **env, t_shell *shell)
{
	char	*current_path;

	shell->no_env = 1;
	current_path = NULL;
	current_path = getcwd(current_path, sizeof((int *)100));
	env[0] = ft_strdup("USER=minishell");
	env[1] = ft_strjoin("PWD=", current_path);
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = ft_strdup("TERM=xterm-256color");
	env[6] = NULL;
	free(current_path);
}

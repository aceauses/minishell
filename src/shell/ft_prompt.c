/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:37:21 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/27 11:49:21 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_status(t_shell *shell)
{
	if (shell->current_status != NULL)
		free(shell->current_status);
	if (shell->exit_code == 0)
		shell->current_status = ft_strdup(shell->status_s);
	else if (shell->exit_code > 0)
		shell->current_status = ft_strdup(shell->status_f);
}

void prepare_prompt(t_shell *shell)
{
	check_status(shell);
	// char *cwd = getcwd(NULL, 0);
	// char *short_cwd = cwd;	
	// char *last_slash = ft_strrchr(cwd, '/');
	// if (last_slash != NULL) {
	// 	last_slash++;
	// 	char *second_last_slash = ft_strrchr(cwd, '/');
	// 	if (second_last_slash != NULL) {
	// 		second_last_slash++;
	// 		short_cwd = second_last_slash;
	// 	}
	// }
	// printf("[%s] %s%s $ %s%s %s ", getenv("TERM_PROGRAM"), BLUE, getenv("USER")
	// 		, YELLOW, short_cwd, RESET);
	// free(cwd);
}


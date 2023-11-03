/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:37:21 by aceauses          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/03 16:51:02 by aceauses         ###   ########.fr       */
=======
/*   Updated: 2023/11/03 16:58:06 by rmitache         ###   ########.fr       */
>>>>>>> ff5faf931b28509998d247377142f846ff96bcb2
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_status(t_shell *shell)
{
	if (shell->status == 0)
		shell->current_status = shell->status_s;
	else if (shell->status > 0)
		shell->current_status = shell->status_f;
}

void prepare_prompt(t_shell *shell)
{
	check_status(shell);
	char *cwd = getcwd(NULL, 0);
	char *short_cwd = cwd;	
	char *last_slash = ft_strrchr(cwd, '/');
	if (last_slash != NULL) {
		last_slash++;
		char *second_last_slash = ft_strrchr(cwd, '/');
		if (second_last_slash != NULL) {
			second_last_slash++;
			short_cwd = second_last_slash;
		}
	}
	printf("[%s] %s%s $ %s%s %s ", getenv("TERM_PROGRAM"), BLUE, getenv("USER")
			, YELLOW, short_cwd, RESET);
	free(cwd);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:37:21 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/14 17:29:54 by aceauses         ###   ########.fr       */
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

void	prepare_prompt(t_shell *shell)
{
	check_status(shell);
	shell->current_status = free_join(shell->current_status, "minishell > ");
}

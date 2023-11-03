/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:40:35 by rmitache          #+#    #+#             */
/*   Updated: 2023/11/03 14:51:06 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_signals(void)
{
	handle_ctrl_c();
}

void	handle_ctrl_c(void)
{
	struct sigaction	sig;
	
	sig.__sigaction_u.__sa_sigaction = do_ctrl_c;
	sig.sa_flags = 0;
	signal(SIGINT, &sig, NULL);
}

void	do_ctrl_c(int signal, siginfo_t *info, void *x)
{
	if (signal == SIGINT)
		printf("SUS\n");
}
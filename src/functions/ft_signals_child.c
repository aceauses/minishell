/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:52:26 by rmitache          #+#    #+#             */
/*   Updated: 2023/11/29 14:11:40 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_ctrl_c_child(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.__sigaction_u.__sa_handler = SIG_DFL;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

static void	signal_ctrl_backslash_child(void)
{
	struct sigaction	ctrl_slash;

	ctrl_slash.__sigaction_u.__sa_sigaction = handle_ctrl_slash;
	ctrl_slash.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_slash.sa_mask);
	sigaction(SIGQUIT, &ctrl_slash, NULL);
}
void	ft_signals_child(struct termios *mirror_termios)
{
	tcsetattr(1, TCSAFLUSH, mirror_termios);
	signal_ctrl_backslash_child();
	signal_ctrl_c_child();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:40:35 by rmitache          #+#    #+#             */
/*   Updated: 2023/12/17 16:34:17 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_signals(struct termios *saved)
{
	struct termios	attr;

	attr = (struct termios){0};
	tcgetattr(0, saved);
	tcgetattr(0, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSAFLUSH, &attr);
	ctrl_slash_settings();
	ctrl_c_settings();
}

void	ctrl_slash_settings(void)
{
	struct sigaction	ctrl_slash;

	ctrl_slash.__sigaction_u.__sa_handler = SIG_IGN;
	ctrl_slash.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_slash.sa_mask);
	sigaction(SIGQUIT, &ctrl_slash, NULL);
}

void	ctrl_c_settings(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.__sigaction_u.__sa_sigaction = handle_ctrl_c;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	handle_ctrl_c(int signal, siginfo_t *info, void *x)
{
	(void)info;
	(void)x;
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_ctrl_c = 1;
	}
}

// void	sig_int_handler_before_exec(int sig_num)
// {
// 	write(1, "x\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	(void)sig_num;
// }

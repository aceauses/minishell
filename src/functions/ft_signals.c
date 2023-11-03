/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:40:35 by rmitache          #+#    #+#             */
/*   Updated: 2023/11/03 18:09:28 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_signals(struct termios *saved)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, saved);
	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);

	ctrl_slash_settings();
	ctrl_c_settings();
}

void	ctrl_slash_settings(void)
{
	struct sigaction	ctrl_slash;

	ctrl_slash.__sigaction_u.__sa_sigaction = handle_ctrl_slash;
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
		prepare_prompt();
		rl_redisplay();
	}
}

void	handle_ctrl_slash(int signal, siginfo_t *info, void *x)
{
	(void)info;
	(void)x;

	if (signal == SIGQUIT)
	{
		prepare_prompt();
		rl_redisplay();
	}
}

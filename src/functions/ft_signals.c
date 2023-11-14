/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:40:35 by rmitache          #+#    #+#             */
/*   Updated: 2023/11/10 16:43:21 by aceauses         ###   ########.fr       */
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

	ctrl_slash.sa_handler = SIG_IGN;
	ctrl_slash.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_slash.sa_mask);
	sigaction(SIGQUIT, &ctrl_slash, NULL);
}

void	ctrl_c_settings(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.sa_handler = SIG_IGN;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void reset_prompt()
{
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
void	handle_ctrl_c(int signal, siginfo_t *info, void *x)
{
	(void)info;
	(void)x;

	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		reset_prompt();
		rl_redisplay();
	}
}


void	handle_ctrl_slash(int signal, siginfo_t *info, void *x)
{
	(void)info;
	(void)x;

	if (signal == SIGQUIT)
	{
		reset_prompt();
		rl_redisplay();
	}
}

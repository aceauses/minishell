/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:50 by aceauses          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/03 17:51:30 by aceauses         ###   ########.fr       */
=======
/*   Updated: 2023/11/03 17:54:30 by rmitache         ###   ########.fr       */
>>>>>>> ff5faf931b28509998d247377142f846ff96bcb2
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **env)
{
	char	**copied;
	int		y;

	y = 0;
	while (env[y] != NULL)
		y++;
	copied = malloc(sizeof(char *) * (y + 1));
	if (!copied)
		return (NULL);
	y = 0;
	while (env[y] != NULL)
	{
		copied[y] = ft_strdup(env[y]);
		y++;
	}
	copied[y] = NULL;
	return (copied);
}

void	init_data(char **ev, t_shell *shell)
{
	shell->env = copy_env(ev);
	if (!shell->env)
		exit(12);
	shell->status_s = ft_strdup("⇥ ");
	shell->status_f = ft_strdup("⥇ ");
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	int		builtin;

	(void)argv;
	builtin = 0;
	if (argc > 1)
		xerror("Hey :(", NULL);
	shell = malloc(sizeof(t_shell));
	init_data(env, shell);
	check_signals(&shell->saved);
	while (1)
	{
<<<<<<< HEAD
		//check_signals();
		prepare_prompt(shell);
		shell->line = readline(shell->current_status);
		if (!shell->line)
			break ;
		builtin = check_builtins(shell->line, shell);
		if (builtin == 1)
=======
		prepare_prompt();
		shell->line = readline("💁");
		if (!shell->line || check_exit(shell->line))
>>>>>>> ff5faf931b28509998d247377142f846ff96bcb2
			break ;
		else if (builtin > 1)
			continue ;
		ft_getreq(shell);
		shell->status = pipex(shell->req, shell->env);
		free(shell->line);
	}
	ft_free(shell->env);
	free(shell); // free everything inside that was allocated with malloc
	free(shell->line);
	return (0);
}

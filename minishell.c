/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/03 10:01:14 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_exit(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'e' && line[i + 1] == 'x' && line[i + 2] == 'i'
		&& line[i + 3] == 't')
		return (printf("exit\n"), 1);
	return (0);
}

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

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

void	env_print(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	init_data(char **ev, t_shell *shell)
{
	shell->env = copy_env(ev);
	if (!shell->env)
		exit(12);
}

void	ft_ctrl(int	signal)
{
	if (signal == 2)
	{
		write(1, "\n", 2);
		rl_on_new_line();
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_shell	*shell;

	(void)argv;
	if (argc > 1)
		xerror("Hey :(", NULL);
	shell = malloc(sizeof(t_shell));
	init_data(env, shell);
	while (1)
	{
		signal(SIGINT, ft_ctrl);
		prepare_prompt();
		line = readline("💁");
		if (check_exit(line))
			break ;
		free(line);
	}
	ft_free(shell->env);
	free(shell); // free everything inside that was allocated with malloc
	free(line);
	system("leaks minishell");
	return (0);
}

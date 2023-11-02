/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/02 15:05:55 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char *line;

	(void)argv;
	(void)env;
	if (argc > 1)
		ft_exit();
	while (1)
	{
		line = readline("minishell$ ");
		printf("Your command:  :P %s\n", line);
		// if (strcmp(line, "exit") == 0)
		// {
		// 	free(line);
		// 	exit(0);
		// }
		free(line);
	}
}

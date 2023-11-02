/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/02 16:24:14 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char *line;

	(void)argv;
	(void)env;
	if (argc > 1)
		xerror("Dont give arguments pls", NULL);
	while (1)
	{
		line = readline("minishell$ ");
		if (strcmp(line, "exit") == 0)
			break ;
		free(line);
	}
	system("leaks minishell");
	return (0);
}

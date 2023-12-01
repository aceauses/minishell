/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:49:28 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/01 18:41:42 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(char *argv, char c)
{
	int	re;

	re = -1;
	if (c == 'R')
		re = access((const char *)argv, R_OK);
	else if (c == 'W')
		re = access((const char *)argv, W_OK);
	else if (c == 'X')
		re = access((const char *)argv, X_OK);
	else
		error("Please give a valid instruction.", NULL);
	return (re);
}

static void	remove_and_put(char **s, int i, char *command)
{
	char	*temp;

	temp = ft_strdup(s[i]);
	free(s[i]);
	s[i] = ft_strtrim(temp, "PATH=");
	free(temp);
	s[i] = free_join(s[i], "/");
	s[i] = free_join(s[i], command);
}

static char	**no_env(char *s)
{
	char	**env;

	env = ft_split(s, ':');
	return (env);
}

char	*find_path(char **path, char *command)
{
	char	**paths;
	char	*save;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (path[j] != NULL && ft_strncmp(path[j], "PATH=", 5) != 0)
		j++;
	paths = ft_split(path[j], ':');
	if (!paths)
		paths = no_env("/bin:/usr/bin");
	if (!command || command[0] == '.' || command[0] == '/')
		return (ft_free_array(paths), NULL);
	save = NULL;
	while (paths[i] != NULL)
	{
		remove_and_put(paths, i, command);
		if (check_access(paths[i], 'X') != -1)
			break ;
		i++;
	}
	if (paths[i] == NULL && check_access(paths[i - 1], 'X') == -1)
		return (ft_free_array(paths), paths = NULL, NULL);
	return (save = ft_strdup(paths[i]), ft_free_array(paths), save);
}

/*Some of the Paths of the commands you can use is
We can use access() to check if we can access this files.*/
int	pipex(char **argv, char *ev[])
{
	int		child1;
	int		child2;
	int		status;
	int		i;
	int		p[2];

	i = 0;
	while (argv[i] != NULL)
	{
		if (pipe(p) < 0)
			exit (EXIT_FAILURE);
		child1 = fork();
		if (child1 < 0)
			error("Failed to init fork", NULL);
		if (child1 == 0)
			child_one(argv[i], ev, p);
		child2 = fork();
		if (child2 < 0)
			error("Failed to init fork", NULL);
		if (child2 == 0)
			child_two(argv[i], ev, p);
		(void) ((close(p[0]) && 0) || (close(p[1]) && 0)
			|| waitpid(child1, &status, 0) < 0 || waitpid(child2, &status, 0));
		i++;
	}
	return (status);
}

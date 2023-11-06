/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:59 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/03 23:07:53 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_command(char *argv)
{
	if (ft_strncmp(argv, "awk", 3) == 0)
		return (ft_strdup("awk"));
	else
		return (ft_strdup("sed"));
}

static int	configure_int(char *argv, int *i, int *special)
{
	if (ft_strncmp(argv, "\'", ft_strlen(argv))
		> (int)ft_strlen(argv))
	{
		while ((argv[*i] == ' ') && argv[*i])
			(*i)++;
		if (argv[*i] == '\"' && argv[*i + 1] == '\'')
			return (0);
		if (argv[*i] == '\"')
		{
			*special = 1;
			(*i)++;
		}
		while (argv[*i] == '\'' && argv[*i])
			(*i)++;
	}
	return (1);
}

static void	copy_command(char *argv, char *r, int i, int special)
{
	int	x;

	x = 0;
	while (argv[i] != '\0' && argv[i])
		if (argv[i] != '\\')
			r[x++] = argv[i++];
	else
		i++;
	r[x] = '\0';
	while (r[x - 1] == '\'' || (r[x - 1] == '\"' && special == 1))
		r[x-- - 1] = '\0';
}

char	**special_command(char *argv)
{
	int		i;
	int		special;
	char	**r;

	i = 4;
	special = 0;
	r = malloc(3 * sizeof(char *));
	if (!r)
		return (NULL);
	r[0] = set_command(argv);
	if (!configure_int(argv, &i, &special))
	{
		r[1] = ft_strdup("\'");
		return (r);
	}
	r[1] = malloc(ft_strlen(argv) * sizeof(char));
	if (!r[1])
		return (NULL);
	copy_command(argv, r[1], i, special);
	r[2] = NULL;
	return (r);
}
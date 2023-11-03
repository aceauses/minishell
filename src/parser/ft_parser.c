/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:01:58 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/03 18:26:12 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	num_words(char const *s, char set)
{
	size_t	i;
	int		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == set) && s[i] != set)
			words++;
		i++;
	}
	return (words);
}

/*ft_getreq:
	A function that will split the shell->line and get each argument after
	pipes if they exist.*/
void	ft_getreq(t_shell *shell)
{
	int		i;
	int		j;
	int		k;
	char	**req;

	i = 0;
	j = 0;
	k = 0;
	req = malloc(sizeof(char *) * num_words(shell->line, '|') + 1);
	if (!req)
		xerror("Malloc error", shell);
	while (shell->line[i] != '\0')
	{
		if (shell->line[i] == '|')
		{
			req[j] = ft_substr(shell->line, k, i - k);
			k = i + 1;
			j++;
		}
		i++;
	}
	req[j] = ft_substr(shell->line, k, i - k);
	req[j + 1] = NULL;
	shell->req = req;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:01:58 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/07 18:49:38 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	num_words(char const *s, char set)
// {
// 	size_t	i;
// 	int		words;

// 	i = 0;
// 	words = 0;
// 	while (s[i])
// 	{
// 		if ((i == 0 || s[i - 1] == set) && s[i] != set)
// 			words++;
// 		i++;
// 	}
// 	return (words);
// }

/*ft_getreq:
	A function that will split the shell->line and get each argument after
	pipes if they exist.*/
void	ft_getreq(t_shell *shell)
{

	shell->req = ft_split(shell->line, '|');
}

void	ft_parser(t_shell *shell)
{
	int	i;

	i = 0;
	ft_getreq(shell);
	while (shell->req[i] != NULL)
	{
		// ft_getargs(shell, i);
		// ft_getcmd(shell, i);
		// ft_getredir(shell, i);
		// ft_getpipe(shell, i);
		i++;
	}
}
 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:50:30 by rmitache          #+#    #+#             */
/*   Updated: 2023/12/09 17:21:15 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_replace_env(char **save, char *type, t_shell *shell)
{
	if (*save == NULL && ft_strlen(type) != 0)
		*save = replace_with_env(make_magic(type), shell);
	else if (ft_strlen(type) != 0)
		*save = ft_strjoin(*save, replace_with_env(type, shell));
}

void	expand_replace_env2(char **save, char *type, t_shell *shell)
{
	if (*save == NULL)
		*save = replace_with_env(type, shell);
	else
		*save = ft_strjoin(replace_with_env(type, shell), *save);
}

void	c_inside_join(char **save, char *s, int i)
{
	if (s[check_inside(s, i + 1) + 1] == ' ')
		*save = ft_strjoin_char(*save, ' ');
}

int	check_inside(char *s, int i)
{
	int	count;

	count = 0;
	while (s[i] != '\0' && s[i] != ')' && s[i] != '$' && s[i] != ' '
		&& s[i] != '(')
	{
		count++;
		i++;
	}
	return (count);
}

void	check_flag(char *s, int *flag, int i)
{
	if (s[i] == '\'')
		*flag *= -1;
}

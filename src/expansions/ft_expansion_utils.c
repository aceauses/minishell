/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:50:30 by rmitache          #+#    #+#             */
/*   Updated: 2023/12/15 19:14:26 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_replace_env(char **save, char *type, t_shell *shell)
{
	char	*tmp;

	if (*save == NULL && ft_strlen(type) != 0)
		*save = replace_with_env(type, shell);
	else if (ft_strlen(type) != 0)
	{
		tmp = replace_with_env(type, shell);
		*save = free_join(*save, tmp);
		free(tmp);
	}
	else
		free(type);
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
		&& s[i] != '(' && s[i] != '"' && s[i] != '\'' && s[i] != '/'
		&& s[i] != '?')
	{
		count++;
		i++;
	}
	if (s[i] == '?')
		count += 1;
	return (count);
}

void	check_flag(char *s, int *flag, int i, int *dq)
{
	if (s[i] == '"' && *dq == 0)
		*dq = 1;
	else if (s[i] == '"' && *dq == 1)
		*dq = 0;
	if (s[i] == '\'' && *dq == 0 && s[i + check_inside(s, i + 1)] != '"')
		*flag *= -1;
}

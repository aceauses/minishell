/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:36:53 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/09 17:21:01 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_magic(char *str)
{
	char	*tmp;
	int		i;
	int		dq;

	i = 0;
	dq = 0;
	tmp = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == DQUOTE)
			dq = 1;
		if (str[i] != DQUOTE && str[i] != SQUOTE)
			tmp = ft_strjoin_char(tmp, str[i]);
		else if (str[i] == SQUOTE && str[i + 1] != SQUOTE)
			tmp = ft_strjoin_char(tmp, str[i]);
		i++;
	}
	if (tmp == NULL)
		tmp = ft_strdup("");
	return (tmp);
}

void	*replace_with_env(char *type, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (ft_strlen(type) == 0)
		return (0);
	if (ft_strncmp(type, "?", 1) == 0)
		return (free(type), ft_itoa(shell->exit_code));
	while (shell->env[i] != NULL)
	{
		if (special_cmp(type, shell->env[i]) == 0)
		{
			tmp = ft_strchr(shell->env[i], '=');
			tmp2 = ft_strdup(tmp + 1);
			free(type);
			return (tmp2);
		}
		i++;
	}
	return (free(type), ft_strdup(""));
}

static	int	should_expand(char *s, int i)
{
	if (s[i] == '$' && s[i + 1] != '\0'
		&& s[i + 1] != '(' && s[i + 1] != ')')
		return (1);
	if (s[i] == '$' && s[i + 1] == '(')
		return (2);
	return (0);
}

char	*check_expansion(char *s, int i, t_shell *shell)
{
	char	*save;
	int		flag;
	char	*type;

	if (s == NULL || ft_strchr(s, '$') == NULL)
		return (s);
	flag = 1;
	i = -1;
	save = NULL;
	while (s[++i] != '\0')
	{
		check_flag(s, &flag, i);
		if (should_expand(s, i) == 1 && flag == 1)
		{
			type = ft_substr(s, i + 1, check_inside(s, i + 1));
			expand_replace_env(&save, type, shell);
			c_inside_join(&save, s, i);
			// free(type);
		}
		if (should_expand(s, i) == 2 && flag == 1)
		{
			type = ft_substr(s, i + 2, check_inside(s, i + 2));
			expand_replace_env2(&save, type, shell);
			i++;
			// free(type);
		}
	}
	return (save);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:36:53 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/16 23:26:33 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*expand(char *type, t_shell *shell, char *s, int *i)
{
	int		j;
	char	*save;

	save = NULL;
	j = ft_strlen(type);
	if (ft_strlen(type) == 0)
		save = ft_strjoin_char(save, '$');
	expand_replace_env(&save, type, shell);
	c_inside_join(&save, s, *i);
	*i += j;
	return (save);
}

static char	*expand2(char *type, t_shell *shell, char *s, int *i)
{
	int		j;
	char	*save;

	save = NULL;
	j = ft_strlen(type);
	if (ft_strlen(type) == 0)
		save = ft_strjoin_char(save, '$');
	expand_replace_env(&save, type, shell);
	c_inside_join(&save, s, *i);
	*i += j + 2;
	return (save);
}

char	*check_expansion(char *s, int i, t_shell *shell)
{
	char	*save;
	int		flag;
	int		dq;
	char	*type;

	flag = 1;
	dq = 0;
	save = ft_calloc(1, 1);
	while (s[++i] != '\0')
	{
		check_flag(s, &flag, i, &dq);
		if (should_expand(s, i) == 1 && flag == 1)
		{
			type = ft_substr(s, i + 1, check_inside(s, i + 1));
			save = free_join2(save, expand(type, shell, s, &i));
		}
		else if (should_expand(s, i) == 2 && flag == 1)
		{
			type = ft_substr(s, i + 2, check_inside(s, i + 2));
			save = free_join2(save, expand2(type, shell, s, &i));
		}
		else
			save = ft_strjoin_char(save, s[i]);
	}
	return (save);
}

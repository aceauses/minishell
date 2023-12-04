/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:36:53 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/04 15:58:02 by aceauses         ###   ########.fr       */
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

static void	*replace_with_env(char *type, t_shell *shell)
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
			return (free(type), tmp2);
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

static int	check_inside(char *s, int i)
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

char	*check_exepansion(char *s, t_shell *shell)
{
	int		i;
	int		flag;
	char *save;
	char *type;

	if (s == NULL || ft_strchr(s, '$') == NULL)
		return (s);
	flag = 1;
	save = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			flag *= -1;
		if (should_expand(s, i) == 1 && flag == 1)
		{
			type = ft_substr(s, i + 1, check_inside(s, i + 1));
			if (save == NULL && ft_strlen(type) != 0)
				save = replace_with_env(make_magic(type), shell);
			else if (ft_strlen(type) != 0)
				save = ft_strjoin(save, replace_with_env(type, shell));
			if (s[check_inside(s, i + 1) + 2] == ' ')
				save = ft_strjoin_char(save, ' ');
			i++;
		}
		if (should_expand(s, i) == 2 && flag == 1)
		{
			type = ft_substr(s, i + 2, check_inside(s, i + 2));
			if (save == NULL)
				save = replace_with_env(type, shell);
			else
				save = ft_strjoin(replace_with_env(type, shell), save);
			i++;
		}
		i++;
	}
	return (save);
}

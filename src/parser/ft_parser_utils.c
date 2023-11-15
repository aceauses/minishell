/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:50:54 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/15 20:44:36 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_counting(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '|')
			count++;
		i++;
	}
	return (count);
}

static void	*replace_with_env(char *type, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (ft_strlen(type) == 0)
		return (0);
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], type, ft_strlen(type)) == 0)
		{
			tmp = ft_strchr(shell->env[i], '=');
			tmp2 = ft_strdup(tmp + 1);
			return (tmp2);
		}
		i++;
	}
	return (ft_strdup(""));
}

int	handle_expansions(t_token *tokens, t_shell *shell)
{
	char	*type;
	int		i;

	i = 0;
	type = NULL;
	while (tokens)
	{
		if (tokens->value[i] == '$' && tokens->value[i + 1] != '\0'
			&& tokens->value[i + 1] != '(')
		{
			type = ft_strdup(tokens->value + i + 1);
			free(tokens->value);
			tokens->value = replace_with_env(type, shell);
		}
		if (tokens->value[i] == '$' && tokens->value[i + 1] == '(')
		{
			type = ft_strdup(tokens->value + i + 2);
			type[ft_strlen(type) - 1] = '\0';
			free(tokens->value);
			tokens->value = replace_with_env(type, shell);
		}
		tokens = tokens->next;
	}
	return (free(type), 0);
}

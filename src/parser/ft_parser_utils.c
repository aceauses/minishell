/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:50:54 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/28 10:33:27 by aceauses         ###   ########.fr       */
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
	if (ft_strncmp(type, "?", 1) == 0)
		return (ft_itoa(shell->exit_code));
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
			&& tokens->value[i + 1] != '(' && tokens->value[i + 1] != ')' &&
			checker(tokens->prev, TOKEN_HERE_DOC) == 0)
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

bool	check_pipe(char *line, int i)
{
	char quote_char = 0;

	for (int k = 0; k < i; k++)
	{
		if ((line[k] == '\'' || line[k] == '"')
			&& (k == 0 || line[k - 1] != '\\'))
		{
			if (!quote_char)
				quote_char = line[k];
			else if (quote_char == line[k])
				quote_char = 0;
		}
	}
	return (quote_char != 0);
}

char	**copy_matrix(char **matrix)
{
	char	**copied;
	int		y;

	y = 0;
	while (matrix && matrix[y] != NULL)
		y++;
	copied = malloc(sizeof(char *) * (y + 1));
	if (!copied)
		return (NULL);
	y = 0;
	while (matrix[y] != NULL)
	{
		copied[y] = ft_strdup(matrix[y]);
		y++;
	}
	copied[y] = NULL;
	return (copied);
}
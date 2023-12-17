/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:50:54 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/17 16:40:52 by rmitache         ###   ########.fr       */
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

int	handle_expansions(t_token *tokens, t_shell *shell)
{
	char	*type;
	int		tmp_i;
	int		i;

	i = 0;
	tmp_i = -1;
	type = NULL;
	while (tokens)
	{
		if (checker(tokens->prev, TOKEN_HERE_DOC) == 0
			&& (tokens->value == NULL || ft_strchr(tokens->value, '$') != NULL))
			type = check_expansion(tokens->value, tmp_i, shell);
		if (type && ft_strchr(tokens->value, '$')
			&& checker(tokens->prev, TOKEN_HERE_DOC) == 0)
		{
			free(tokens->value);
			tokens->value = type;
		}
		tokens = tokens->next;
	}
	return (0);
}

bool	check_pipe(char *line, int i)
{
	char	quote_char;
	int		k;

	quote_char = 0;
	k = -1;
	while (++k < i)
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
	while (matrix && matrix[y] != NULL)
	{
		copied[y] = ft_strdup(matrix[y]);
		y++;
	}
	copied[y] = NULL;
	return (copied);
}

int	allocate_args(char ***args, int args_count, t_token **tokens,
	t_token **current)
{
	*args = (char **)malloc((args_count + 2) * sizeof(char *));
	if (*args == NULL)
		return (1);
	*current = *tokens;
	*current = (*current)->next;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:50:54 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/09 11:28:19 by rmitache         ###   ########.fr       */
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

// static void	*replace_with_env(char *type, t_shell *shell)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*tmp2;

// 	i = 0;
// 	if (ft_strlen(type) == 0)
// 		return (0);
// 	if (ft_strncmp(type, "?", 1) == 0)
// 		return (free(type), ft_itoa(shell->exit_code));
// 	while (shell->env[i] != NULL)
// 	{
// 		if (ft_strncmp(shell->env[i], type, ft_strlen(type)) == 0)
// 		{
// 			tmp = ft_strchr(shell->env[i], '=');
// 			tmp2 = ft_strdup(tmp + 1);
// 			return (free(type), tmp2);
// 		}
// 		i++;
// 	}
// 	return (free(type), ft_strdup(""));
// }

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
		if (checker(tokens->prev, TOKEN_HERE_DOC) == 0)
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
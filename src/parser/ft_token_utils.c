/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:29:20 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/16 12:13:48 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(char *content, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(content);
	new->type = type;
	new->next = NULL;
	return (new);
}

int	find_token_type(char *line)
{
	if (ft_strncmp(line, ">>", 2) == 0)
		return (REDIR_APP);
	if (ft_strncmp(line, "<<", 2) == 0)
		return (TOKEN_HERE_DOC);
	if (ft_strncmp(line, ">", 1) == 0)
		return (REDIR_OUT);
	if (ft_strncmp(line, "<", 1) == 0)
		return (REDIR_IN);
	return (TOKEN_WORD);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		if (tmp)
		{
			tmp->prev = NULL;
		}
		tokens = tmp;
	}
}

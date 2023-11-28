/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:29:20 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/27 18:47:15 by rmitache         ###   ########.fr       */
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
	if (ft_strcmp(line, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(line, ">") == 0)
		return (REDIR_OUT);
	if (ft_strcmp(line, ">>") == 0)
		return (REDIR_APP);
	if (ft_strcmp(line, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(line, "<<") == 0)
		return (TOKEN_HERE_DOC);
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

void	token_print(t_token *tokens)
{
	printf("%sPrinting tokens:%s\n", RED, RESET);
	while (tokens)
	{
		printf("Value: %s\n", tokens->value);
		printf("Type: %d\n", tokens->type);
		if (tokens->prev)
		{
			printf("------Prev-------\n");
			printf("Previous Value: %s\n", tokens->prev->value);
			printf("Previous Type: %d\n", tokens->prev->type);
			printf("------Prev-END---\n");
		}
		else
		{
			printf("------Prev-------\n");
			printf("Previous: (NULL)\n");
			printf("------Prev-END----\n");
		}
		tokens = tokens->next;
	}
	printf("%sEnd of tokens%s\n", RED, RESET);
}

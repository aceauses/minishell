/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:54:47 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/15 20:45:00 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*put_cmd(t_token *tokens)
{
	if (tokens->type == TOKEN_WORD && tokens->prev == NULL)
		return (ft_strdup(tokens->value));
	if (tokens->type == TOKEN_REDIRECTION_IN)
		return (NULL); // maybe change fds
	if (tokens->type == TOKEN_REDIRECTION_OUT)
		return (NULL); // maybe change fds
	return (NULL);
}

static char	*put_heredoc(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_HERE_DOC)
		{
			if (tmp->next->type == TOKEN_WORD)
				return (ft_strdup(tmp->next->value));
			else
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	**extract_args(t_token *tokens)
{
	char	**args;
	int		args_count;
	t_token	*current;
	int		i;

	current = tokens;
	current = current->next;
	args_count = count_args(tokens);
	args = (char **)malloc((args_count + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	current = tokens;
	current = current->next;
	i = 0;
	while (current != NULL && current->type == TOKEN_WORD)
	{
		args[i] = ft_strdup(current->value);
		if (args[i] == NULL)
			return (NULL);
		i++;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

static char	*extract_redirs(t_token *tokens)
{
	t_token	*current;
	char	*redir;

	current = tokens;
	redir = NULL;
	while (current)
	{
		if (current->type == TOKEN_REDIRECTION_IN)
			redir = ft_strdup("<");
		if (current->type == TOKEN_REDIRECTION_OUT)
			redir = ft_strdup(">");
		current = current->next;
	}
	return (redir);
}

t_cmd_table	*create_table(t_token *tokens, int index)
{
	t_cmd_table	*node;

	node = prepare_cmd_table();
	node->cmd = put_cmd(tokens);
	node->heredoc = put_heredoc(tokens);
	node->args = extract_args(tokens);
	node->redir = extract_redirs(tokens);
	node->index = index;
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:54:47 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/17 16:50:55 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*put_cmd(t_token *tokens)
{
	if (checker(tokens, TOKEN_WORD) && tokens->prev == NULL)
		return (ft_strdup(tokens->value));
	if (is_redirs(tokens) && tokens->prev == NULL)
		return (first_redirections(tokens)); // maybe change fds
	return (NULL);
}

static char	*put_heredoc(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (checker(tmp, TOKEN_HERE_DOC))
		{
			if (checker(tmp->next, TOKEN_WORD))
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

	args_count = count_args(tokens);
	args = (char **)malloc((args_count + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	current = tokens;
	current = current->next;
	i = 0;
	while (checker(current, TOKEN_WORD))
	{
		if (is_redirs(current->prev))
		{
			if (current->next != NULL)
				current = current->next;
			if (current->next == NULL)
				return (free(args), NULL);
			current = current->next;
		}
		args[i] = ft_strdup(current->value);
		if (args[i] == NULL)
			return (NULL);
		i++;
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

static t_redir	*extract_redirs(t_token *tokens)
{
	t_token		*current;
	t_redir		*redir_list;
	t_redir		*new_redir;

	redir_list = NULL;
	current = tokens;
	while (current)
	{
		if (checker(current, TOKEN_REDIRECTION_IN)
			|| checker(current, TOKEN_REDIRECTION_OUT))
		{
			new_redir = malloc(sizeof(t_token));
			if (!new_redir)
				return (NULL);
			new_redir->type = current->type;
			if (checker(current->next, TOKEN_WORD))
				new_redir->file_name = ft_strdup(current->next->value);
			else
				new_redir->file_name = NULL;
			new_redir->next = NULL;
			redir_list = append_token(redir_list, new_redir);
		}
		current = current->next;
	}
	return (redir_list);
}

t_cmd_table	*create_table(t_token *tokens, int index)
{
	t_cmd_table	*node;

	node = prepare_cmd_table();
	node->cmd = put_cmd(tokens);
	node->heredoc = put_heredoc(tokens);
	node->args = extract_args(tokens);
	node->redir_list = extract_redirs(tokens);
	node->index = index;
	return (node);
}
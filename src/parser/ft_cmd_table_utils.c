/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_table_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:52:27 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/15 22:35:24 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_table(t_cmd_table *table)
{
	t_cmd_table	*next_table;
	t_redir		*next_redir;

	while (table)
	{
		next_table = table->next;
		while (table->redir_list)
		{
			next_redir = table->redir_list->next;
			free(table->redir_list->file_name);
			free(table->redir_list);
			table->redir_list = next_redir;
		}
		free(table->cmd);
		free(table->heredoc);
		ft_free(table->args);
		ft_free(table->exec_args);
		free(table);
		table = next_table;
	}
}

t_cmd_table	*prepare_cmd_table(void)
{
	t_cmd_table	*new;

	new = malloc(sizeof(t_cmd_table));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = NULL;
	new->exec_args = NULL;
	new->heredoc = NULL;
	new->redir_list = NULL;
	new->index = -1;
	new->next = NULL;
	return (new);
}

t_cmd_table	*add_to_cmd_table(t_cmd_table *head, t_cmd_table *new_node)
{
	t_cmd_table	*current;

	if (!head)
		return (new_node);
	current = head;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new_node;
	return (head);
}

int	count_args(t_token *current)
{
	int		i;

	i = 0;
	while (current != NULL && current->type == TOKEN_WORD)
	{
		i++;
		current = current->next;
	}
	if (current != NULL && is_redirs(current))
		i++;
	return (i);
}

char	*first_redirections(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (checker(tmp, REDIR_IN)
		|| checker(tmp, REDIR_OUT))
	{
		if (checker(tmp->next, TOKEN_WORD))
		{
			if (tmp->next->next != NULL
				&& tmp->next->next->type == TOKEN_WORD)
			{
				token = token->next->next;
				return (ft_strdup(tmp->next->next->value));
			}
			else
				return (NULL);
		}
	}
	return (NULL);
}

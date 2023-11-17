/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_table_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:52:27 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/17 16:40:55 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_table(t_cmd_table *table)
{
	t_cmd_table	*tmp;

	while (table)
	{
		tmp = table->next;
		while (table->redir_list)
		{
			t_redir *tmp = table->redir_list->next;
			free(table->redir_list->file_name);
			free(table->redir_list);
			table->redir_list = tmp;
		}
		free(table->cmd);
		free(table->heredoc);
		ft_free(table->args);
		free(table);
		table = tmp;
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
	if (tmp->type == TOKEN_REDIRECTION_IN
		|| tmp->type == TOKEN_REDIRECTION_OUT)
		{
			if (tmp->next->type == TOKEN_WORD)
			{
				if (tmp->next->next != NULL
					&& tmp->next->next->type == TOKEN_WORD)
						return (ft_strdup(tmp->next->next->value));
				else
					return (NULL);
			}
		}
	return (NULL);
}

void print_cmd_table(t_cmd_table *cmd_table)
{
    while (cmd_table != NULL)
    {
        printf("%s---TABLE-[%d]---%s\n", GREEN, cmd_table->index, RESET);
        printf("Index: %d\n", cmd_table->index);
        printf("Command: %s\n", cmd_table->cmd);
        printf("Heredoc: %s\n", cmd_table->heredoc);
		int i = 0;
		while (cmd_table->args && cmd_table->args[i])
		{
			printf("Arg: %s\n", cmd_table->args[i]);
			i++;
		}
		t_redir *tmp = cmd_table->redir_list;
		while (tmp)
		{
			printf("Redir: %d\n", tmp->type);
			printf("File: %s\n", tmp->file_name);
			tmp = tmp->next;
		}
		printf("%s---TABLE-END---%s\n", GREEN, RESET);
		cmd_table = cmd_table->next;
	}
}

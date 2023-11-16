/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_table_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:52:27 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/16 17:38:20 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_table(t_cmd_table *table)
{
	t_cmd_table	*tmp;

	while (table)
	{
		tmp = table->next;
		free(table->cmd);
		free(table->heredoc);
		free(table->redir);
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
	new->redir = NULL;
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
	return (i);
}

char	*first_redirections(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp != NULL)
	{
		if (tmp->type == TOKEN_REDIRECTION_IN
			|| tmp->type == TOKEN_REDIRECTION_OUT)
			{
				if (tmp->next->type == TOKEN_WORD
					&& tmp->next->next->type == TOKEN_WORD)
					return (ft_strdup(tmp->next->next->value));
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
		while (cmd_table->args[i])
		{
			printf("Arg: %s\n", cmd_table->args[i]);
			i++;
		}
        printf("Redir: %s\n", cmd_table->redir);
        printf("%s---TABLE-END---%s\n", GREEN, RESET);

        cmd_table = cmd_table->next;
    }
}

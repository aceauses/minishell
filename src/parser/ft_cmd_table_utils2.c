/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_table_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:52:22 by rmitache          #+#    #+#             */
/*   Updated: 2023/12/01 18:31:23 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirs(t_token *tokens)
{
	if (tokens != NULL && (tokens->type == REDIR_IN
		|| tokens->type == REDIR_OUT
		|| tokens->type == REDIR_APP || tokens->type == TOKEN_HERE_DOC))
		return (1);
	return (0);
}

int	checker(t_token *tokens, t_type type)
{
	if (tokens != NULL && tokens->type == type)
		return (1);
	return (0);
}

t_redir	*append_redir(t_redir *head, t_redir *new_token)
{
	t_redir		*last;

	if (!head)
		return (new_token);
	last = head;
	while (last->next)
		last = last->next;
	last->next = new_token;
	return (head);
}

t_redir *create_redir(t_token *current, int type)
{
	t_redir		*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	if (IS_REDIR(current->value[1]) && ((current->value[2] != '\0') ||
		!checker(current->next, TOKEN_WORD)))
		new_redir->file_name = ft_strdup(current->value + 2);
	else if ((ft_isalnum(current->value[1])  || current->value[1] == '.'
			|| current->value[1] == '/') && (current->value[1] != '\0'
			|| !checker(current->next, TOKEN_WORD)))
		new_redir->file_name = ft_strdup(current->value + 1);
	else if (checker(current->next, TOKEN_WORD))
		new_redir->file_name = ft_strdup(current->next->value);
	else
		new_redir->file_name = NULL;
	new_redir->next = NULL;
	return (new_redir);
}

char	**no_args(t_cmd_table *table)
{
	char	**args;

	args = (char **)malloc(2 * sizeof(char *));
	if (args == NULL)
		return (NULL);
	args[0] = ft_strdup(table->cmd);
	args[1] = NULL;
	return (args);
}

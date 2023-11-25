/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_table_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:52:22 by rmitache          #+#    #+#             */
/*   Updated: 2023/11/25 21:54:42 by aceauses         ###   ########.fr       */
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

t_redir	*append_token(t_redir *head, t_redir *new_token)
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

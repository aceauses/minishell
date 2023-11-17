/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_table_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:51:46 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/17 14:46:28 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirs(t_token *tokens)
{
	if (tokens != NULL && (tokens->type == TOKEN_REDIRECTION_IN
		|| tokens->type == TOKEN_REDIRECTION_OUT
		|| tokens->type == TOKEN_APPEND || tokens->type == TOKEN_HERE_DOC))
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

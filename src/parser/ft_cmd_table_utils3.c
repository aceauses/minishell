/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_table_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:27:45 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/05 14:49:40 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_cmd(t_token *tokens)
{
	if (checker(tokens, TOKEN_WORD) && tokens->prev == NULL)
		return (ft_strdup(tokens->value));
	if (is_redirs(tokens) && tokens->prev == NULL)
		return (first_redirections(tokens));
	return (NULL);
}

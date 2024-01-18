/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:21:24 by rmitache          #+#    #+#             */
/*   Updated: 2023/12/16 19:19:23 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*do_magic(char *str)
{
	int		i;
	char	quote;
	char	*res;

	res = ft_strdup("");
	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quote == 0)
				quote = str[i++];
			else if (str[i] == quote)
			{
				quote = 0;
				i++;
			}
			else
				res = ft_strjoin_char(res, str[i++]);
		}
		else
			res = ft_strjoin_char(res, str[i++]);
	}
	return (res);
}

void	remove_echo_quotes(char **str)
{
	char	*tmp;
	int		pos;

	pos = 0;
	while (str[pos] != NULL)
	{
		tmp = do_magic(str[pos]);
		free(str[pos]);
		str[pos] = tmp;
		pos++;
	}
}

void	remove_quotes_redir(t_redir *redir_list)
{
	char	*tmp;

	while (redir_list != NULL)
	{
		if (redir_list->file_name != NULL)
		{
			tmp = do_magic(redir_list->file_name);
			free(redir_list->file_name);
			redir_list->file_name = tmp;
		}
		redir_list = redir_list->next;
	}
}

void	remove_quotes_table(t_cmd_table *whole_table)
{
	char	*tmp;

	while (whole_table != NULL)
	{
		if (whole_table->cmd != NULL && has_quotes(whole_table->cmd) == 1)
		{
			tmp = do_magic(whole_table->cmd);
			free(whole_table->cmd);
			whole_table->cmd = tmp;
		}
		if (ft_strcmp(whole_table->cmd, "echo") == 1
			&& ft_strcmp(whole_table->cmd, "/bin/echo") == 1)
		{
			remove_quotes_args(whole_table->args);
			remove_quotes_redir(whole_table->redir_list);
		}
		else
			remove_echo_quotes(whole_table->args);
		whole_table = whole_table->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:21:24 by rmitache          #+#    #+#             */
/*   Updated: 2023/12/09 17:21:42 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*single_start_in_rm(char *str)
{
	char	*tmp;
	int		q;
	int		i;
	int		sq;

	i = 0;
	sq = 0;
	q = has_quotes(str);
	tmp = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == SQUOTE)
			sq = 1;
		if (str[i] == ' ' && str[i + 1] == ' ' && q == 0)
			while (str[i] == ' ')
				i++;
		if (str[i] != SQUOTE && str[i] != DQUOTE)
			tmp = ft_strjoin_char(tmp, str[i]);
		else if (str[i] == DQUOTE && sq == 1)
			tmp = ft_strjoin_char(tmp, str[i]);
		i++;
	}
	if (tmp == NULL)
		tmp = ft_strdup("");
	return (tmp);
}

char	*do_magic(char *str, int i, int dq)
{
	char	*tmp;
	int		q;

	q = has_quotes(str);
	tmp = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == DQUOTE)
			dq = !dq;
		if (str[i] == SQUOTE && dq != 1)
			return (single_start_in_rm(str));
		if (str[i] == ' ' && str[i + 1] == ' ' && q == 0)
			while (str[i] == ' ' && str[i] != '\0')
				i++;
		if (str[i] != DQUOTE && str[i] != SQUOTE)
			tmp = ft_strjoin_char(tmp, str[i]);
		else if (str[i] == SQUOTE && dq == 1)
			tmp = ft_strjoin_char(tmp, str[i]);
		i++;
	}
	if (tmp == NULL)
		tmp = ft_strdup("");
	return (tmp);
}

void	remove_echo_quotes(char **str, int i, int dq)
{
	char	*tmp;
	int		pos;

	pos = 0;
	while (str[pos] != NULL)
	{
		tmp = do_magic(str[pos], i, dq);
		free(str[pos]);
		str[pos] = tmp;
		pos++;
	}
}

void	remove_quotes_redir(t_redir *redir_list, int i, int dq)
{
	char	*tmp;

	while (redir_list != NULL)
	{
		if (redir_list->file_name != NULL)
		{
			tmp = do_magic(redir_list->file_name, i, dq);
			free(redir_list->file_name);
			redir_list->file_name = tmp;
		}
		redir_list = redir_list->next;
	}
}

void	remove_quotes_table(t_cmd_table *whole_table)
{
	char	*tmp;
	int		i;
	int		dq;

	i = 0;
	dq = 0;
	while (whole_table != NULL)
	{
		if (whole_table->cmd != NULL && has_quotes(whole_table->cmd) == 1)
		{
			tmp = do_magic(whole_table->cmd, i, dq);
			free(whole_table->cmd);
			whole_table->cmd = tmp;
		}
		if (ft_strcmp(whole_table->cmd, "echo") == 1
			&& ft_strcmp(whole_table->cmd, "/bin/echo") == 1)
		{
			remove_quotes_args(whole_table->args, i, dq);
			remove_quotes_redir(whole_table->redir_list, i, dq);
		}
		else
			remove_echo_quotes(whole_table->args, i, dq);
		whole_table = whole_table->next;
	}
}

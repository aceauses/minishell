/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:21:24 by rmitache          #+#    #+#             */
/*   Updated: 2023/11/29 18:54:53 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_start_end(char *str, int start, int end)
{
	int		i;
	char	*memory;

	if (str == NULL || start < 0 || end < start)
		return (NULL);
	memory = (char *)malloc(end - start + 1);
	if (memory == NULL)
		return (NULL);
	i = -1;
	while (start + ++i < end)
		memory[i] = str[start + i];
	memory[i] = '\0';
	return (memory);
}

char	*rm_quotes(char *str)
{
	char	*res;

	if (str[0] == '"' || str[0] == '\'')
	{
		res = ft_strdup_start_end(str, 1, ft_strlen(str) - 1);
		return (res);
	}
	else
		return (ft_strdup(str));
}


static bool	has_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
	}
	return (0);
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*res;
	int		i;

	if (str == NULL)
	{
		res = (char *)malloc(2);
		res[0] = c;
		res[1] = '\0';
		return (res);
	}
	res = (char *)malloc(ft_strlen(str) + 2);
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i++] = c;
	res[i] = '\0';
	free(str);
	return (res);
}

static char	*single_start_in_rm(char *str)
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

static char	*do_magic(char *str)
{
	char	*tmp;
	int		q;
	int		i;
	int		dq;

	i = 0;
	dq = 0;
	q = has_quotes(str);
	tmp = NULL;
	while (str[i] != '\0')
	{
		if (str[0] == SQUOTE)
		{
			tmp = single_start_in_rm(str);
			return (tmp);
		}
		if (str[i] == DQUOTE)
			dq = 1;
		if (str[i] == ' ' && str[i + 1] == ' ' && q == 0)
			while (str[i] == ' ')
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

static void remove_quotes_args(char **args)
{
	int		i;
	char	*tmp;
	
	i = -1;
	while (args[++i])
	{
		tmp = do_magic(args[i]);
		free(args[i]);
		args[i] = tmp;
	}
}

static void	remove_echo_quotes(char **str)
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
		if (whole_table->cmd != NULL)
		{
			tmp = do_magic(whole_table->cmd);
			free(whole_table->cmd);
			whole_table->cmd = tmp;
		}
		if (ft_strcmp(whole_table->cmd, "echo") == 1 && ft_strcmp(whole_table->cmd, "/bin/echo") == 1)
		{
			remove_quotes_args(whole_table->args);
			remove_quotes_redir(whole_table->redir_list);
		}
		else
			remove_echo_quotes(whole_table->args);
		whole_table = whole_table->next;
	}
}

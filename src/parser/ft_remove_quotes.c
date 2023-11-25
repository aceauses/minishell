/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:21:24 by rmitache          #+#    #+#             */
/*   Updated: 2023/11/25 20:28:37 by aceauses         ###   ########.fr       */
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

static void remove_quotes_args(char **args)
{
	char	*tmp;
	int		i;
	
	i = -1;
	while (args[++i])
	{
		tmp = rm_quotes(args[i]);
		free(args[i]);
		args[i] = tmp;
	}
}


static void	do_magic(char **str, int pos, int str_len, int inside_double)
{
	int		starts_with;
	int		ends_with;

	starts_with = IS_QUOTE(str[pos][0]);
	ends_with = IS_QUOTE(str[pos][str_len - 1]);
	inside_double = 0;
	if (ends_with && starts_with)
		str[pos] = ft_strdup_start_end(str[pos], 1, str_len - 1);
	else if (ends_with)
		str[pos] = ft_strdup_start_end(str[pos], 0, str_len - 1);
	else if (starts_with)
		str[pos] = ft_strdup_start_end(str[pos], 1, str_len);
}

static void	remove_echo_quotes(char **str)
{
	int	pos;
	int	inside_double;
	int	str_len;

	pos = 0;
	inside_double = 0;
	str_len = 0;
	while (str[pos] != NULL)
	{
		str_len = (int)ft_strlen(str[pos]);
		if (str[pos][0] == '\"' && inside_double == 0)
			inside_double = 1;
		do_magic(str, pos, str_len, inside_double);
		pos++;
	}
}

void	remove_quotes_table(t_cmd_table *whole_table)
{
	char	*tmp;

	while (whole_table != NULL)
	{
		if (whole_table->cmd != NULL)
		{
			tmp = rm_quotes(whole_table->cmd);
			free(whole_table->cmd);
			whole_table->cmd = tmp;
		}
		if (ft_strcmp(whole_table->cmd, "echo") == 1)
			remove_quotes_args(whole_table->args);
		else
			remove_echo_quotes(whole_table->args); // SHOULD FREE SIR!
		whole_table = whole_table->next;
	}
}

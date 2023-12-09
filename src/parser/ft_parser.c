/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:01:58 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/05 15:31:46 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skipping_quotes(char *str, int index)
{
	int	quote;

	if (str[index] != SQUOTE && str[index] != DQUOTE)
		return (index);
	quote = str[index++];
	while (str[index] != quote)
	{
		if (str[index] == '\0')
			return (index);
		index++;
	}
	return (index);
}

char	**split_pipes(char *line, char set)
{
	char	**splitted;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	splitted = malloc(sizeof(char *) * (pipe_counting(line) + 2));
	while (line[i])
	{
		if (line[i] == set && (!check_pipe(line, i)
				&& !check_pipe(line, i)))
		{
			splitted[j] = ft_substr(line, k, i - k);
			while (line[i] == set && line[i + 1] == set)
				i++;
			k = i + 1;
			j++;
		}
		i++;
	}
	splitted[j] = ft_substr(line, k, i - k);
	splitted[j + 1] = NULL;
	return (splitted);
}

int	skipping_spaces(char *str, int index)
{
	while ((str[index] == ' ' && str[index + 1] == ' ')
		|| (str[index] == '\t' && str[index + 1] == '\t')
		|| (str[index] == '\t' && str[index + 1] == ' ')
		|| (str[index] == ' ' && str[index + 1] == '\t'))
		index++;
	return (index);
}

char	**splitter(char *line, char set)
{
	char	**splitted;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	splitted = malloc(sizeof(char *) * (num_words(line, SPACES) + 1));
	while (line[i])
	{
		i = skipping_quotes(line, i);
		if (set_char(line[i], SPACES))
		{
			splitted[j] = ft_substr(line, k, i - k);
			k = i + 1;
			j++;
		}
		i = skipping_spaces(line, i);
		i++;
	}
	if (line[i - 1] != set)
		splitted[j] = ft_substr(line, k, i - k);
	splitted[j + 1] = NULL;
	return (free(line), splitted);
}

int	ft_parser(t_shell *shell)
{
	int		i;
	char	**splitted;
	char	**split_tokens;

	i = -1;
	shell->cmd_table = NULL;
	splitted = split_pipes(shell->trimmed_line, '|');
	while (splitted[++i] != NULL)
	{
		split_tokens = NULL;
		split_tokens = splitter(custom_trim(splitted[i], SPACES), ' ');
		shell->cmd_table = create_tokens(split_tokens, i, shell->cmd_table, \
			shell);
		ft_free(split_tokens);
	}
	// t_cmd_table	*tmp = shell->cmd_table;
	// print_cmd_table(tmp);
	// free_cmd_table(tmp);
	return (free(splitted), 0);
}

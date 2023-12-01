/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:01:58 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/01 18:36:15 by aceauses         ###   ########.fr       */
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

char	**splitter(char *line, char set)
{
	char	**splitted;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	splitted = malloc(sizeof(char *) * (num_words(line, ' ') + 1));
	while (line[i])
	{
		i = skipping_quotes(line, i);
		if (line[i] == set && line[i + 1] != set)
		{
			splitted[j] = ft_substr(line, k, i - k);
			k = i + 1;
			j++;
		}
		i++;
	}
	if (line[i - 1] != set)
		splitted[j] = ft_substr(line, k, i - k);
	splitted[j + 1] = NULL;
	return (free(line), splitted);
}

t_cmd_table	*create_tokens(char **splitted, int in, t_cmd_table *cmd_table_head,
		t_shell *shell)
{
	t_token	*token;
	t_token	*current;
	int		i;

	i = 0;
	token = ft_new_token(splitted[i], find_token_type(splitted[i]));
	token->prev = NULL;
	current = token;
	while (splitted[++i])
	{
		current->next = ft_new_token(splitted[i], find_token_type(splitted[i]));
		current->next->prev = current;
		current = current->next;
	}
	current = token;
	handle_expansions(current, shell);
	cmd_table_head = add_to_cmd_table(cmd_table_head, create_table(token, in));
	return (free_tokens(token), cmd_table_head);
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

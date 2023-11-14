/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:01:58 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/14 21:07:09 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (line[i] == set && line[i - 1] != SQUOTE && line[i - 1] != DQUOTE)
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

t_cmd_table *create_tokens(char **splitted, int in, t_cmd_table *cmd_table_head)
{
	t_token	*head;
	t_token	*current;
	int		i;

	i = 0;
	head = ft_new_token(splitted[i], find_token_type(splitted[i]));
	head->prev = NULL;
	current = head;
	while (splitted[++i])
	{
		current->next = ft_new_token(splitted[i], find_token_type(splitted[i]));
		current->next->prev = current;
		current = current->next;
	}
	cmd_table_head = add_to_cmd_table(cmd_table_head, create_table(head, in));
	return (token_print(head), free_tokens(head), cmd_table_head);
}

int	ft_parser(t_shell *shell)
{
	int		i;
	t_token	*token;
	char	**splitted;
	char	**split_tokens;

	i = -1;
	shell->cmd_table = NULL;
	splitted = split_pipes(shell->trimmed_line, '|');
	while (splitted[++i] != NULL)
	{
		split_tokens = NULL;
		split_tokens = ft_split(splitted[i], ' ');
		shell->cmd_table = create_tokens(split_tokens, i, shell->cmd_table);
		ft_free(split_tokens);
	}
	print_cmd_table(shell->cmd_table);
	free_cmd_table(shell->cmd_table);
	ft_free(splitted);
	return (0);
}

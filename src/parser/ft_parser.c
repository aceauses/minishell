/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:01:58 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/17 17:00:10 by rmitache         ###   ########.fr       */
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

static int	has_quotes(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
			return (1);
	}
	return (0);
}

char	*removing_quotes(t_token *token)
{
	int	i;

	if (has_quotes(token->value))
	{
		i = -1;
		while(token->value[++i] != '\0')
		{
			if (token->value[i] == '\'')
				printf("SINGLE FOUND SIRR\n");
		}
	}
	return (token->value);
}

static void	handle_quotes(t_token *current, t_shell *shell)
{
	char	*tmp;
	t_token	*head;

	head = current;
	// do not change original next, use a temp bro
	if (has_quotes(shell->trimmed_line))
	{
		while (current)
		{
			if (current->type == TOKEN_HERE_DOC)
			{
				if (current->next != NULL)
					current = current->next;
				else
					return ;
			}
			tmp = removing_quotes(current);
			current = current->next;
		}
	}
	current = head;
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
	handle_quotes(current, shell);
	cmd_table_head = add_to_cmd_table(cmd_table_head, create_table(token, in));
	return (token_print(token), free_tokens(token), cmd_table_head);
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
		split_tokens = ft_split(splitted[i], ' ');
		shell->cmd_table = create_tokens(split_tokens, i, shell->cmd_table, \
			shell);
		ft_free(split_tokens);
	}
	print_cmd_table(shell->cmd_table);
	free_cmd_table(shell->cmd_table);
	return (ft_free(splitted), 0);
}

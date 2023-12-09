/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:35:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/05 14:57:26 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_words(char const *s, char *set)
{
	size_t	i;
	int		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if ((i == 0 || ft_strchr(set, s[i - 1]) != NULL)
			&& ft_strchr(set, s[i]) == NULL)
			words++;
		i++;
	}
	return (words);
}

int	set_char(char s, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Custom version of ft_strtrim that trims and frees the original string
 * 
 * @param s1 
 * @param set 
 * @return char* 
 */
char	*custom_trim(char const *s1, char const *set)
{
	char	*mem;
	size_t	end;
	size_t	start;
	size_t	j;

	start = 0;
	while (s1[start] && set_char(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (set_char(s1[end - 1], set) && end > start)
		end--;
	mem = malloc(end - start + 1);
	if (!mem)
		return (NULL);
	if (!s1)
		return (free(mem), NULL);
	j = 0;
	while (start < end)
		mem[j++] = s1[start++];
	mem[j] = '\0';
	free((char *)s1);
	return (mem);
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

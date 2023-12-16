/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:54:47 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/16 12:17:30 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*put_heredoc(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (checker(tmp, TOKEN_HERE_DOC))
		{
			if (ft_isprint(tmp->value[2]) == 1)
				return (ft_strdup(tmp->value + 2));
			else if (checker(tmp->next, TOKEN_WORD))
				return (ft_strdup(tmp->next->value));
			else
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	**extract_args(t_token *tokens, int i, int args_count, char **args)
{
	t_token	*current;

	if (allocate_args(&args, args_count) == 1)
		return (NULL);
	current = tokens;
	current = current->next;
	while (checker(current, TOKEN_WORD))
	{
		if (is_redirs(current->prev))
		{
			if (current->next != NULL)
				current = current->next;
			if (current->next == NULL)
				return (free(args), NULL);
			current = current->next;
		}
		args[i] = ft_strdup(current->value);
		if (args[i] == NULL)
			return (NULL);
		i++;
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	return (args[i] = NULL, args);
}

static t_redir	*extract_redirs(t_token *tokens)
{
	t_token		*current;
	t_redir		*redir_list;
	t_redir		*new_redir;

	redir_list = NULL;
	current = tokens;
	while (current)
	{
		if (checker(current, REDIR_IN) || checker(current, TOKEN_HERE_DOC)
			|| checker(current, REDIR_OUT) || checker(current, REDIR_APP))
		{
			new_redir = create_redir(current, current->type);
			redir_list = append_redir(redir_list, new_redir);
		}
		current = current->next;
	}
	return (redir_list);
}

char	**extract_exec_args(t_cmd_table *cmd_table)
{
	int		i;
	char	**exec_args;
	char	**args_tables;

	i = 0;
	if (cmd_table->cmd == NULL)
		return (NULL);
	if (cmd_table->args == NULL)
		return (no_args(cmd_table));
	args_tables = copy_matrix(cmd_table->args);
	if (args_tables == NULL)
		return (NULL);
	while (args_tables[i] != NULL)
		i++;
	if (i < 1 && cmd_table->cmd == NULL)
		return (ft_free(args_tables), NULL);
	exec_args = (char **)malloc(sizeof(char *) * (i + 2));
	if (exec_args == NULL)
		return (ft_free(args_tables), NULL);
	exec_args[0] = ft_strdup(cmd_table->cmd);
	i = -1;
	while (args_tables[++i] != NULL)
		exec_args[i + 1] = ft_strdup(args_tables[i]);
	exec_args[i + 1] = NULL;
	return (ft_free(args_tables), exec_args);
}

t_cmd_table	*create_table(t_token *tokens, int index)
{
	t_cmd_table	*node;
	int			norm_i;
	int			args_count;
	char		**args;

	norm_i = 0;
	args = NULL;
	args_count = count_args(tokens);
	node = prepare_cmd_table();
	node->cmd = put_cmd(tokens);
	node->heredoc = put_heredoc(tokens);
	node->args = extract_args(tokens, norm_i, args_count, args);
	node->redir_list = extract_redirs(tokens);
	if (node->args != NULL)
		remove_quotes_table(node);
	node->exec_args = extract_exec_args(node);
	node->index = index;
	return (node);
}

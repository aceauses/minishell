/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:36:19 by rmitache          #+#    #+#             */
/*   Updated: 2023/12/03 16:49:58 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tilda(t_shell *shell)
{
	char	*tmp;

	if (shell->trimmed_line[0] == '/' && shell->trimmed_line[1] == '\0')
	{
		ft_dprintf(2, "minishell: %s: is a directory\n", shell->trimmed_line);
		shell->exit_code = 126;
		return (1);
	}
	if (shell->no_env == 1)
		tmp = ft_strdup("/Users/minishell");
	else
		tmp = ft_strdup(check_home(shell->env));
	if (tmp == NULL)
		tmp = ft_strdup("/Users/minishell");
	if (shell->trimmed_line[0] == '~' && (shell->trimmed_line[1] == '\0'
			|| shell->trimmed_line[1] == ' '))
	{
		shell->exit_code = 126;
		return (ft_dprintf(2, "%s is a directory\n", tmp), free(tmp), 1);
	}
	return (free(tmp), 0);
}

int	output_redir(t_shell *shell)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(shell->trimmed_line);
	if (shell->trimmed_line[l - 1] == '<')
		return (syntax_error("newline"), 1);
	while (shell->trimmed_line[i] != '<' && shell->trimmed_line[i])
		i++;
	if (shell->trimmed_line[i] == '<' && shell->trimmed_line[i + 1] == '<')
	{
		if (shell->trimmed_line[i + 2] != '<'
			&& shell->trimmed_line[i + 2] != '\0')
			return (0);
		if (shell->trimmed_line[i + 2] == '<')
			return (syntax_error("<"), 1);
		else
			return (syntax_error("newline"), 1);
	}
	else if (shell->trimmed_line[i] == '<'
		&& shell->trimmed_line[i + 1] == '\0')
		return (syntax_error("newline"), 1);
	return (0);
}

int	input_redir(t_shell *shell)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(shell->trimmed_line);
	if (shell->trimmed_line[l - 1] == '>')
		return (syntax_error("newline"), 1);
	while (shell->trimmed_line[i] != '>' && shell->trimmed_line[i])
		i++;
	if (shell->trimmed_line[i] == '>' && shell->trimmed_line[i + 1] == '>')
	{
		if (shell->trimmed_line[i + 2] != '>'
			&& shell->trimmed_line[i + 2] != '\0')
			return (0);
		if (shell->trimmed_line[i + 2] == '>')
			return (syntax_error(">"), 1);
		else
			return (syntax_error("newline"), 1);
	}
	else if (shell->trimmed_line[i] == '>'
		&& shell->trimmed_line[i + 1] == '\0')
		return (syntax_error("newline"), 1);
	return (0);
}

int	extra_redirect(t_shell *shell)
{
	if (ft_strchr(shell->trimmed_line, '>') && input_redir(shell) == 1)
	{
		shell->exit_code = 2;
		return (1);
	}
	else if (ft_strchr(shell->trimmed_line, '<') && output_redir(shell) == 1)
	{
		shell->exit_code = 2;
		return (1);
	}
	if (inp_next_to_out(shell->trimmed_line) == 1)
	{
		shell->exit_code = 2;
		return (syntax_error("newline"), 1);
	}
	return (0);
}

void	syntax_error(char *line)
{
	ft_dprintf(2, "syntax error near unexpected token '%s'\n", line);
}

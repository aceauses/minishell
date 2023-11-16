/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:36:19 by rmitache          #+#    #+#             */
/*   Updated: 2023/11/16 18:31:18 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tilda(t_shell *shell)
{
	char	*tmp;

	if (shell->no_env == 1)
		tmp = "/Users/minishell";
	else
		tmp = shell->env[5];
	if (*tmp == 'H' && *(tmp + 1) == 'O' && *(tmp + 2) == 'M'
		&& *(tmp + 3) == 'E' && *(tmp + 4) == '=')
		tmp = (char *)tmp + 5;
	if (shell->trimmed_line[0] == '~' && (shell->trimmed_line[1] == '\0'
			|| shell->trimmed_line[1] == ' '))
	{
		shell->exit_code = 126;
		return (printf("%s is a directory\n", tmp), 1);
	}
	return (0);
}

int	output_redir(t_shell *shell)
{
	int	i;

	i = 0;
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

	i = 0;
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
	if (ft_strchr(shell->trimmed_line, '>')
		&& ft_strchr(shell->trimmed_line, '<'))
	{
		shell->exit_code = 2;
		return (syntax_error("newline"), 1);
	}
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
	return (0);
}

void	syntax_error(char *line)
{
	printf("syntax error near unexpected token '%s'\n", line);
}

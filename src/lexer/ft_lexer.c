/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:26:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/15 22:25:37 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(t_shell *shell)
{
	char	*line;
	int		double_q;
	int		single_q;

	double_q = 0;
	single_q = 0;
	line = shell->trimmed_line;
	while (*line != '\0')
	{
		if (*line == '"')
			double_q++;
		if (*line == '\'')
			single_q++;
		line++;
	}
	if (single_q == 1)
		return (syntax_error("'"), 1);
	else if (double_q == 1)
		return (syntax_error("\""), 1);
	if (double_q % 2 != 0 || single_q % 2 != 0)
		return (ft_putstr_fd("Error: quotes not closed\n", 2), 1);
	return (0);
}

static int	op_n_pipe(t_shell *shell)
{
	char	*line;

	line = shell->trimmed_line;
	if (!ft_strchr(line, '\'') && !ft_strchr(line, '"'))
	{
		if (check_operator(line, '<') == 1 || check_operator(line, '>') == 1
			|| ft_strnstr(line, ">>|", ft_strlen(line))
			|| ft_strnstr(line, "<<|", ft_strlen(line)))
		{
			shell->exit_code = 2;
			return (syntax_error("|"), 1);
		}
	}
	return (0);
}

static int	check_pipes(t_shell *shell)
{
	int	len;

	len = ft_strlen(shell->trimmed_line);
	if ((shell->trimmed_line[0] == '|' || shell->trimmed_line[len - 1] == '|'))
	{
		shell->exit_code = 2;
		return (syntax_error("|"), 1);
	}
	return (0);
}

static int	line_valid(t_shell *shell)
{
	if (ft_strlen(shell->trimmed_line) == 0 || tilda(shell) == 1
		|| extra_redirect(shell) == 1)
		return (1);
	return (0);
}

/*A function that will check the input give for problems*/
// Maybe implement check of the string.
int	lexer(t_shell *shell)
{
	if (line_valid(shell) == 1 || check_quotes(shell) == 1
		|| op_n_pipe(shell) == 1 || check_pipes(shell) == 1)
		return (1);
	else
		return (0);
}

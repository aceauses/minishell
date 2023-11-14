/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:26:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/14 17:05:09 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(t_shell *shell)
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

/* static void	*replace_with_env(char *type, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], type, ft_strlen(type)) == 0)
		{
			tmp = ft_strchr(shell->env[i], '=');
			tmp2 = ft_strdup(tmp + 1);
			return (tmp2);
		}
		i++;
	}
	return (0);
}

static int	handle_expansions(char *line, t_shell *shell, int place)
{
	char	*type;
	int		i;

	i = 0;
	type = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && line[i + 1] != '\0' && line[i + 1] != '(')
			type = ft_strdup(line + i + 1);
		if (line[i] == '$' && line[i + 1] == '(')
		{
			type = ft_strdup(line + i + 2);
			type[ft_strlen(type) - 1] = '\0';
		}
		i++;
	}
	if (type == NULL)
		return (0);
	free(shell->tokens[place].value);
	shell->tokens[place].value = replace_with_env(type, shell);
	return (free(type), 0);
} */

int	op_n_pipe(t_shell *shell)
{
	char	*line;

	line = shell->trimmed_line;
	if (ft_strncmp(line, "<|", 2) == 0 && line[2] == '\0')
	{
		shell->exit_code = 2;
		return (syntax_error("newline"), 1);
	}
	else if (ft_strncmp(line, "<|", 2) == 0 && line[2] != '\0')
	{
		shell->exit_code = 2;
		return (syntax_error("|"), 1);
	}
	else if (ft_strncmp(line, ">|", 2) == 0 && line[2] == '\0')
	{
		shell->exit_code = 2;
		return (syntax_error("newline"), 1);
	}
	else if (ft_strncmp(line, ">|", 2) == 0 && line[2] != '\0')
	{
		shell->exit_code = 2;
		return (syntax_error("|"), 1);
	}
	else
		return (0);
}

int	check_pipes(t_shell *shell)
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

int	line_valid(t_shell *shell)
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

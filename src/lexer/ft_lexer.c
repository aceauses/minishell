/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:26:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/09 20:43:28 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipes(char *line);

static	int	line_valid(char *line)
{
	if (line[0] == '\0' || line == NULL || line[0] == ' ')
		return (1);
	if (!check_pipes(line))
		return (1);
	return (0);
}

static void	remove_quotes(char *line)
{
	int	i;
	int	d_flag;
	int	s_flag;

	i = 0;
	d_flag = 0;
	s_flag = 0;
	while (line[i])
	{
		if (line[i] == '"' && s_flag == 0)
		{
			d_flag = 1;
			line[i] = ' ';
		}
		if (line[i] == '\'' && d_flag == 0)
		{
			s_flag = 1;
			line[i] = ' ';
		}
		i++;
	}
}

static int	check_quotes(char *line)
{
	int	i;
	int	double_q;
	int	single_q;

	i = 0;
	double_q = 0;
	single_q = 0;
	while (line[i])
	{
		if (line[i] == '"')
			double_q++;
		if (line[i] == '\'')
			single_q++;
		i++;
	}
	if (double_q % 2 != 0 || single_q % 2 != 0)
		return (ft_putstr_fd("Error: quotes not closed\n", 2), 1);
	remove_quotes(line);
	return (0);
}

static void	tokenizer(char *line, t_shell *shell)
{
	char	**token;
	int		i;

	shell->tokens = malloc(sizeof(t_token_s) * 100);
	if (!shell->tokens)
		exit(12);
	token = ft_split(line, ' ');
	i = -1;
	while (token[++i] != NULL)
	{
		if (ft_strcmp(token[i], "|") == 0)
			shell->tokens[i].type = TOKEN_PIPE;
		else if (ft_strcmp(token[i], "<<") == 0)
			shell->tokens[i].type = TOKEN_HERE_DOC;
		else if (ft_strcmp(token[i], ">>") == 0)
			shell->tokens[i].type = TOKEN_APPEND;
		else if (ft_strcmp(token[i], "<") == 0)
			shell->tokens[i].type = TOKEN_REDIRECTION_IN;
		else if (ft_strcmp(token[i], ">") == 0)
			shell->tokens[i].type = TOKEN_REDIRECTION_OUT;
		else
			shell->tokens[i].type = TOKEN_WORD;
		shell->tokens[i].value = ft_strdup(token[i]);
	}
	shell->tokens[i].value = NULL;
	shell->tokens[i].type = -1;
	ft_free(token);
}

static void	*replace_with_env(char *type, t_shell *shell)
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
}

static int	check_pipes(char *line)
{
	int	i;
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	i = ft_strlen(tmp) - 1;
	if (tmp[0] == '|')
		return (ft_putstr_fd(BAD_PIPE, 2),free(tmp), 1);
	if (tmp[i] == '|')
		return (ft_putstr_fd(BAD_PIPE, 2),free(tmp), 1);
	return (free(tmp), 0);
}

/*A function that will check the input give for problems*/
// Maybe implement check of the string.
int	lexer(char *line, t_shell *shell)
{
	int	i;

	i = 0;
	if (!line_valid(line))
		return (1);
	tokenizer(line, shell);
	// for (int i = 0; shell->tokens[i].value != NULL; i++)
	// 	printf("token[%d] = [%u]\n", i, shell->tokens[i].type);
	while (shell->tokens[i].value != NULL)
	{
		if (!check_quotes(shell->tokens[i].value))
			return (1); // also add free tokens function
		if (!handle_expansions(shell->tokens[i].value, shell, i))
			return (1);
		i++;
	}
	// for (int i = 0; shell->tokens[i].value != NULL; i++)
	// 	printf("token[%d] = [%s]\n", i, shell->tokens[i].value);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:26:50 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/08 16:31:02 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static	int	line_valid(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\0' || line == NULL)
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

static int	tokenizer(char *line, t_shell *shell)
{
	char	**token;
	int		i;

	shell->tokens = malloc(sizeof(t_token_s) * (ft_strlen(line) + 1));
	if (!shell->tokens)
		return (1);
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
	return (ft_free(token), 0);
}

// static void	replace_with_env(char *type, t_shell *shell, char *line)
// {
// 	int		i;
// 	char	*env;
// 	char	*tmp;
// 	char	*tmp2;

// 	i = 0;
// 	while (shell->env[i] != NULL)
// 	{
// 		if (ft_strncmp(shell->env[i], type + 1, ft_strlen(type + 1)) == 0)
// 		{
// 			env = ft_strdup(shell->env[i]);
// 			tmp = ft_strchr(env, '=');
// 			tmp2 = ft_strdup(tmp + 1);
// 			free(line);
// 			line = ft_strdup(tmp2);
// 			free(env);
// 			free(tmp2);
// 			return ;
// 		}
// 		i++;
// 	}
// }

static int	handle_expansions(char *line, t_shell *shell)
{
	char	*type;
	int		i;
	int		k;

	i = 0;
	k = 0;
	(void)shell;
	type = NULL;
	if (ft_strcmp(line, "$"))
	{
		while (line[i] != '\0')
		{
			if (line[i] == '$')
				type = ft_strdup(line + i);
			i++;
		}
	}
	else
		return (0);
	printf("type = [%s]\n", type);
	// replace_with_env(type, shell, line);
	return (0);
}

/*A function that will check the input give for problems*/
// Maybe implement check of the string.
int	lexer(char *line, t_shell *shell)
{
	int	i;

	i = 0;
	if (line_valid(line)) // check line if its valid
		return (free(line), 0);
	if (tokenizer(line, shell)) // check if tokenizer failed
		return (free(line), 0);
	for (int i = 0; shell->tokens[i].value != NULL; i++)
		printf("token[%d] = [%u]\n", i, shell->tokens[i].type);
	while (shell->tokens[i].value != NULL)
	{
		if (check_quotes(shell->tokens[i].value))
			return (free(line), 0); // also add free tokens function
		if (handle_expansions(shell->tokens[i].value, shell))
			return (free(line), 0);
		i++;
	}
	for (int i = 0; shell->tokens[i].value != NULL; i++)
		printf("token[%d] = [%s]\n", i, shell->tokens[i].value);
	printf("lexer [%s]\n", line);
	return (1);
}

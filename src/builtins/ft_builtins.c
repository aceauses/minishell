/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:08:45 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/15 12:56:56 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char	*cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd_table *cmd_table, t_shell *shell, int flag)
{
	int		code;
	int		k;
	int		j;

	code = 0;
	k = 0;
	j = 0;
	if (ft_strcmp(cmd_table->cmd, "echo") == 0)
		code = ft_echo(cmd_table->exec_args);
	if (ft_strcmp(cmd_table->cmd, "exit") == 0 && flag == 0)
		code = ft_exit(cmd_table->exec_args, shell);
	else if (ft_strcmp(cmd_table->cmd, "env") == 0)
		code = ft_env(shell->env);
	else if (ft_strcmp(cmd_table->cmd, "pwd") == 0)
		code = ft_pwd(shell);
	else if (ft_strcmp(cmd_table->cmd, "export") == 0)
		code = ft_export(cmd_table->exec_args, shell);
	else if (ft_strcmp(cmd_table->cmd, "cd") == 0)
		code = ft_cd(cmd_table->exec_args, shell->env);
	else if (ft_strcmp(cmd_table->cmd, "unset") == 0)
		code = ft_unset(cmd_table->exec_args, shell->env, k, j);
	return (code);
}

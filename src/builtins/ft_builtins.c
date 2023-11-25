/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:08:45 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/25 21:57:52 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char	*cmd)
{
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell)
{
	int		code;

	code = 0;
	// if (ft_strcmp(shell->cmd_table->cmd, "echo") == 0)
	// 	ft_echo(shell->cmd_table->exec_args);
	// else if (ft_strcmp(shell->cmd_table->cmd, "unset") == 0)
	// 	ft_unset(shell->cmd_table->exec_args, shell->env);
	if (ft_strcmp(shell->cmd_table->cmd, "exit") == 0)
		ft_exit(shell->cmd_table->exec_args, shell);
	else if (ft_strcmp(shell->cmd_table->cmd, "env") == 0)
		code = ft_env(shell->env);
	else if (ft_strcmp(shell->cmd_table->cmd, "pwd") == 0)
		code = ft_pwd(shell);
	else if (ft_strcmp(shell->cmd_table->cmd, "export") == 0)
		code = ft_export(shell->cmd_table->exec_args, shell);
	else if (ft_strcmp(shell->cmd_table->cmd, "cd") == 0)
		code = ft_cd(shell->cmd_table->exec_args, shell->env);
	return (code);
}

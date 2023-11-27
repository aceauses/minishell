/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:58:53 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/27 15:58:35 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redir_in(t_redir *redir)
{
	int	fd;

	if (check_access(redir->file_name, 'R') < 0)
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", redir->file_name);
		exit(1);
	}
	fd = open(redir->file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", redir->file_name);
		exit(2);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_redir_out(t_redir *redir)
{
	int	fd;

	if (check_access(redir->file_name, 'W') < 0)
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", redir->file_name);
		exit(1);
	}
	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", redir->file_name);
		exit(2);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_redir_append(t_redir *redir)
{
	int	fd;

	if (check_access(redir->file_name, 'W') < 0)
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", redir->file_name);
		exit(1);
	}
	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", redir->file_name);
		exit(2);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/**
 * @brief Handles the input redirection.
 * 
 * @param redir 
 */
void	handle_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			handle_redir_in(tmp);
		else if (tmp->type == REDIR_OUT)
			handle_redir_out(tmp);
		else if (tmp->type == REDIR_APP)
			handle_redir_append(tmp);
		tmp = tmp->next;
	}
}

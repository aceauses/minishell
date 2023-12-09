/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:01:12 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/05 17:00:17 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	xerror(char *s, void *data)
{
	printf("%s\n", s);
	if (data != NULL)
		free(data);
	exit(0);
}

void	fd_error(void)
{
	ft_dprintf(2, "minishell: %s\n", strerror(errno));
	exit(1);
}

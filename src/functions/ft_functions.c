/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:26:00 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/16 23:27:42 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_join2(char *buffer, char *buff)
{
	char	*temp;

	temp = ft_strjoin_gnl(buffer, buff);
	free(buffer);
	free(buff);
	return (temp);
}

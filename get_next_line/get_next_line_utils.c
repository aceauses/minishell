/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:00:27 by aceauses          #+#    #+#             */
/*   Updated: 2023/11/27 16:17:38 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t count, size_t size)
{
	char	*memory;
	size_t	i;

	memory = malloc(count * size);
	if (!memory)
		return (free(memory), NULL);
	i = 0;
	while (i < count * size)
	{
		memory[i] = 0;
		i++;
	}
	return (memory);
}

char	*ft_strjoin_gnl(char const *line, char const *new_line)
{
	char	*mem;
	int		x;
	int		i;

	if (!line || !new_line)
		return (NULL);
	mem = malloc(ft_strlen_mod(line) + ft_strlen_mod(new_line) + 1);
	if (!mem)
		return (NULL);
	i = 0;
	x = 0;
	while (line[x] != '\0')
		mem[i++] = line[x++];
	x = 0;
	while (new_line[x] != '\0')
		mem[i++] = new_line[x++];
	mem[i] = '\0';
	return (mem);
}

size_t	ft_strlen_mod(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *str, int c)
{
	char	cr;

	cr = (char)c;
	while (*str != '\0')
	{
		if (*str == cr)
			return ((char *)str);
		str++;
	}
	while (cr == '\0')
		return ((char *)str);
	return (NULL);
}

char	*free_join(char *buffer, char *buff)
{
	char	*temp;

	temp = ft_strjoin_gnl(buffer, buff);
	free(buffer);
	return (temp);
}
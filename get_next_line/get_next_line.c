/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:12:47 by aceauses          #+#    #+#             */
/*   Updated: 2023/12/14 20:30:33 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_text_fd(int fd, char *buffer)
{
	char	*tmp;
	int		bytes_readed;

	if (!buffer)
		buffer = ft_calloc_gnl(1, 1);
	tmp = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	bytes_readed = 1;
	while (bytes_readed > 0)
	{
		bytes_readed = read(fd, tmp, BUFFER_SIZE);
		if (bytes_readed == -1)
			return (free(tmp), tmp = NULL, free(buffer), buffer = NULL, NULL);
		tmp[bytes_readed] = '\0';
		buffer = free_join(buffer, tmp);
		if (ft_strchr_gnl(tmp, '\n'))
			break ;
	}
	return (free(tmp), buffer);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (buffer[i] == '\0' || buffer == NULL)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc_gnl(i + 2, sizeof(char));
	if (line == NULL)
		return (free(buffer), free(line), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\n';
	if (buffer[i] == '\0')
		line[i] = '\0';
	return (line);
}

static void	*update_buffer(char *buffer)
{
	char	*new;
	int		j;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new = ft_calloc_gnl((ft_strlen_mod(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		new[j++] = buffer[i++];
	return (free(buffer), new);
}
/* [100000] == 'aaaaaa\n
				bbbbbb\n
				cccccc\n
				dddddd'*/

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), buffer = NULL, NULL);
	buffer = get_text_fd(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = get_line(buffer);
	if (line == NULL)
		return (free(buffer), buffer = NULL, free(line), line = NULL, NULL);
	buffer = update_buffer(buffer);
	if (buffer == NULL)
		free(buffer);
	return (line);
}

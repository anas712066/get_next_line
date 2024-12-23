/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 19:26:13 by mumajeed          #+#    #+#             */
/*   Updated: 2024/12/23 20:38:51 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_buffer(char *buffer, char *temp, ssize_t bytes_read)
{
	char	*new_buffer;

	temp[bytes_read] = '\0';
	new_buffer = ft_strjoin(buffer, temp);
	if (buffer)
		free(buffer);
	return (new_buffer);
}

static char	*read_until_newline(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;

	temp = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(temp);
			return (buffer);
		}
		buffer = append_buffer(buffer, temp, bytes_read);
		if (!buffer)
		{
			free(temp);
			return (NULL);
		}
	}
	free(temp);
	return (buffer);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*newline_pos;
	char	*new_buffer;

	newline_pos = ft_strchr(*buffer, '\n');
	if (!newline_pos)
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (line);
	}
	line = ft_substr(*buffer, 0, newline_pos - *buffer + 1);
	new_buffer = ft_strdup(newline_pos + 1);
	free(*buffer);
	*buffer = new_buffer;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147473647)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = read_until_newline(fd, buffer);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (extract_line(&buffer));
}

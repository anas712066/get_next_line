/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:14:32 by mumajeed          #+#    #+#             */
/*   Updated: 2024/12/23 19:05:04 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(t_buffer *buffer, int fd)
{
	char	temp_buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		newline_index;
	char	*line;
	char	*line;

	newline_index = find_newline(buffer->content, buffer->size);
	while (newline_index < 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (buffer->size == 0)
				return (NULL);
			line = append_to_line(NULL, buffer->content, buffer->size);
			clear_buffer(buffer);
			return (line);
		}
		buffer->content = append_to_line(buffer->content, temp_buffer,
				bytes_read);
		buffer->size += bytes_read;
		newline_index = find_newline(buffer->content, buffer->size);
	}
	line = append_to_line(NULL, buffer->content, newline_index + 1);
	buffer->content += newline_index + 1;
	buffer->size -= newline_index + 1;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buffer	*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer == NULL)
		buffer = create_buffer();
	return (extract_line(buffer, fd));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:46 by sdossa            #+#    #+#             */
/*   Updated: 2025/07/18 14:08:00 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_chardup(char *res)
{
	res = malloc(sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

static	char	*ft_fetch_next_line(char *buffer, size_t l_len)
{
	char	*next_line;

	next_line = malloc(l_len + 1);
	if (!next_line)
		return (NULL);
	ft_memmove(next_line, buffer, l_len);
	next_line[l_len] = '\0';
	return (next_line);
}

static char	*fetch_next_line(char **buffer_ptr)
{
	char		*new_line;
	char		*new_line_pos;
	char		*buffer;
	char		*temp;
	size_t		l_len;

	buffer = *buffer_ptr;
	new_line_pos = ft_strchr(buffer, '\n');
	if (new_line_pos)
		l_len = new_line_pos - buffer + 1;
	else
		l_len = ft_strlen(buffer);
	new_line = ft_fetch_next_line(buffer, l_len);
	if (!new_line)
		return (NULL);
	if (new_line_pos)
	{
		temp = ft_strdup(new_line_pos + 1);
		free(buffer);
		*buffer_ptr = temp;
	}
	else
		return (free(buffer), *buffer_ptr = NULL, new_line);
	return (new_line);
}

static char	*ft_fetch_lignes(int fd, char *lines)
{
	char	*buf;
	int		read_bytes;
	int		size;

	if (!lines)
		lines = ft_chardup(lines);
	size = ft_strlen(lines);
	buf = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	read_bytes = 1;
	while (!ft_strchr(buf, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buf), free(lines), NULL);
		buf[read_bytes] = '\0';
		if (read_bytes == 0)
			break ;
		lines = ft_strjoin(lines, buf, size, read_bytes);
		size += read_bytes;
	}
	return (free(buf), lines);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_fetch_lignes(fd, buf);
	if (!buf || buf[0] == '\0')
		return (free(buf), buf = NULL, NULL);
	line = fetch_next_line(&buf);
	if (!line || line[0] == '\0')
		return (free(buf), free(line), NULL);
	return (line);
}

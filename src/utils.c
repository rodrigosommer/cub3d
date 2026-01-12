/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*add_newline_to_line(char *line, int line_len)
{
	char	*new_line;
	int		i;

	new_line = malloc(line_len + 2);
	if (!new_line)
		return (line);
	i = 0;
	while (i < line_len)
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\n';
	new_line[i + 1] = '\0';
	free(line);
	return (new_line);
}

static int	read_buffer_if_needed(int fd, char *buffer,
	int *buffer_pos, int *buffer_size)
{
	if (*buffer_pos >= *buffer_size)
	{
		*buffer_size = read(fd, buffer, 1024);
		*buffer_pos = 0;
		if (*buffer_size <= 0)
			return (0);
	}
	return (1);
}

static int	process_buffer_char(char *buffer, int *buffer_pos,
	char *line, int *line_len)
{
	if (buffer[*buffer_pos] == '\n')
	{
		(*buffer_pos)++;
		return (1);
	}
	line[(*line_len)++] = buffer[(*buffer_pos)++];
	return (0);
}

static char	*build_line(int fd, int *line_len)
{
	static char	buffer[1024];
	static int	buffer_pos;
	static int	buffer_size;
	char		*line;

	line = malloc(1024);
	if (!line)
		return (NULL);
	*line_len = 0;
	while (1)
	{
		if (!read_buffer_if_needed(fd, buffer, &buffer_pos, &buffer_size))
		{
			if (*line_len == 0)
			{
				free(line);
				return (NULL);
			}
			break ;
		}
		if (process_buffer_char(buffer, &buffer_pos, line, line_len))
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	int		line_len;

	line = build_line(fd, &line_len);
	if (!line)
		return (NULL);
	line[line_len] = '\0';
	if (line_len > 0 && line[line_len - 1] != '\n')
		return (add_newline_to_line(line, line_len));
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_element(char *line, t_game *game)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (parse_textures(line, game));
	else if (line[0] == 'S' && line[1] == 'O')
		return (parse_textures(line, game));
	else if (line[0] == 'W' && line[1] == 'E')
		return (parse_textures(line, game));
	else if (line[0] == 'E' && line[1] == 'A')
		return (parse_textures(line, game));
	else if (line[0] == 'F')
		return (parse_colors(line, game));
	else if (line[0] == 'C')
		return (parse_colors(line, game));
	return (0);
}

static int	all_elements_parsed(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->texture_paths[i])
			return (0);
		i++;
	}
	if (game->floor_color == -1 || game->ceiling_color == -1)
		return (0);
	return (1);
}

static int	parse_elements(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	while (line && !all_elements_parsed(game))
	{
		if (!is_empty_line(line) && !parse_element(line, game))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!all_elements_parsed(game))
	{
		if (line)
			free(line);
		return (0);
	}
	if (line)
		free(line);
	return (1);
}

int	parse_file(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		error_exit("Cannot open file");
		return (0);
	}
	if (!parse_elements(fd, game) || !parse_map(fd, game))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

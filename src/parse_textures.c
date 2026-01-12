/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_index(char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (NORTH);
	else if (line[0] == 'S' && line[1] == 'O')
		return (SOUTH);
	else if (line[0] == 'E' && line[1] == 'A')
		return (EAST);
	else if (line[0] == 'W' && line[1] == 'E')
		return (WEST);
	return (-1);
}

static char	*extract_path(char *line)
{
	int		i;
	int		start;
	int		end;
	char	*path;

	i = 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	end = i;
	if (start == end)
		return (NULL);
	path = malloc(end - start + 1);
	if (!path)
		return (NULL);
	i = 0;
	while (start < end)
		path[i++] = line[start++];
	path[i] = '\0';
	return (path);
}

int	parse_textures(char *line, t_game *game)
{
	int		index;
	char	*path;

	index = get_texture_index(line);
	if (index == -1)
	{
		error_exit("Invalid texture identifier");
		return (0);
	}
	if (game->texture_paths[index])
	{
		error_exit("Duplicate texture definition");
		return (0);
	}
	path = extract_path(line);
	if (!path)
	{
		error_exit("Invalid texture path");
		return (0);
	}
	game->texture_paths[index] = path;
	return (1);
}

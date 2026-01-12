/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	finalize_map(t_game *game, char **temp_map, int y)
{
	temp_map[y] = NULL;
	game->map_height = y;
	game->map = temp_map;
	if (y == 0)
	{
		error_exit("Empty map");
		return (0);
	}
	return (1);
}

void	process_special_char(char *line, t_game *game, int *x, int y)
{
	if (line[*x] == '2')
	{
		init_sprite(game, *x, y);
		line[*x] = '0';
	}
	else if (line[*x] == 'T')
	{
		game->tombstone_x = *x + 0.5;
		game->tombstone_y = y + 0.5;
		game->has_tombstone = 1;
		line[*x] = '0';
	}
}

int	read_map_lines(int fd, t_game *game, char ***temp_map, int *capacity)
{
	char	*line;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (y >= *capacity - 1 && !expand_map_capacity(temp_map, capacity))
			return (-1);
		(*temp_map)[y] = ft_strdup(line);
		if (!process_map_line((*temp_map)[y], game, y))
		{
			free(line);
			cleanup_map_on_error(*temp_map, y);
			return (-1);
		}
		y++;
		free(line);
		line = get_next_line(fd);
	}
	return (y);
}

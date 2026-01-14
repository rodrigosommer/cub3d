/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_direction(t_game *game, char dir)
{
	if (dir == 'N')
		set_north_direction(game);
	else if (dir == 'S')
		set_south_direction(game);
	else if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

static void	init_player(t_game *game, int x, int y, char dir)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	game->player.pitch = 0.0;
	init_player_direction(game, dir);
}

static int	process_map_char(char *line, t_game *game, int *x, int y)
{
	static int	player_found = 0;
	char		player_dir;

	if (!is_valid_char(line[*x]))
	{
		error_exit_with_cleanup(game, "Invalid character in map");
		return (0);
	}
	if (!handle_player_char(line[*x], &player_found, &player_dir, game))
		return (0);
	if (line[*x] == 'N' || line[*x] == 'S' || line[*x] == 'E'
		|| line[*x] == 'W')
	{
		init_player(game, *x, y, player_dir);
		line[*x] = '0';
	}
	else
		process_special_char(line, game, x, y);
	return (1);
}

int	process_map_line(char *line, t_game *game, int y)
{
	int	x;

	x = 0;
	while (line[x] && line[x] != '\n')
	{
		if (!process_map_char(line, game, &x, y))
			return (0);
		x++;
	}
	if (x > game->map_width)
		game->map_width = x;
	return (1);
}

int	parse_map(int fd, t_game *game)
{
	char	**temp_map;
	int		y;
	int		capacity;

	game->num_sprites = 0;
	capacity = 100;
	temp_map = malloc(sizeof(char *) * capacity);
	if (!temp_map)
		return (0);
	y = read_map_lines(fd, game, &temp_map, &capacity);
	if (y == -1)
		return (0);
	return (finalize_map(game, temp_map, y));
}

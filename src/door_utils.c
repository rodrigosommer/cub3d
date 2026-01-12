/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*find_door(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->num_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (&game->doors[i]);
		i++;
	}
	return (NULL);
}

static int	get_door_orientation(t_game *game, int x, int y)
{
	if ((x > 0 && x < game->map_width - 1)
		&& (game->map[y][x - 1] == '1'
		&& game->map[y][x + 1] == '1'))
		return (0);
	return (1);
}

static void	add_door(t_game *game, int x, int y)
{
	game->doors[game->num_doors].x = x;
	game->doors[game->num_doors].y = y;
	game->doors[game->num_doors].state = DOOR_CLOSED;
	game->doors[game->num_doors].animation_timer = 0.0;
	game->doors[game->num_doors].animation_progress = 0.0;
	game->doors[game->num_doors].orientation = get_door_orientation(game, x, y);
	game->num_doors++;
}

void	init_doors(t_game *game)
{
	int	x;
	int	y;

	game->num_doors = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'D')
				add_door(game, x, y);
			x++;
		}
		y++;
	}
}

int	is_door_tile(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (0);
	return (game->map[y][x] == 'D' || game->map[y][x] == 'O');
}

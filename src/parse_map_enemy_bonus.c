/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_enemy_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_pos	find_player_in_row(char **map, int y, int width)
{
	t_pos	pos;
	int		x;

	x = 0;
	while (x < width)
	{
		if (map[y][x] == 'N' || map[y][x] == 'S'
			|| map[y][x] == 'E' || map[y][x] == 'W')
		{
			pos.x = x;
			pos.y = y;
			return (pos);
		}
		x++;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

static t_pos	find_player_position(char **map, int height, int width)
{
	t_pos	pos;
	int		y;

	y = 0;
	while (y < height)
	{
		pos = find_player_in_row(map, y, width);
		if (pos.x != -1)
			return (pos);
		y++;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

static int	try_add_enemy(char **map, t_pos player, int dx, int dy)
{
	int	nx;
	int	ny;

	nx = player.x + dx;
	ny = player.y + dy;
	if (nx >= 0 && ny >= 0 && map[ny][nx] == '0')
	{
		map[ny][nx] = '2';
		return (1);
	}
	return (0);
}

void	add_enemy_near_player(char **map, int height, int width)
{
	t_pos	player;

	player = find_player_position(map, height, width);
	if (player.x == -1 || player.y == -1)
		return ;
	if (try_add_enemy(map, player, 1, 0))
		return ;
	if (try_add_enemy(map, player, -1, 0))
		return ;
	if (try_add_enemy(map, player, 0, 1))
		return ;
	try_add_enemy(map, player, 0, -1);
	(void)height;
	(void)width;
}

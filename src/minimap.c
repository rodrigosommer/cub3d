/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsommer <rsommer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:00:00 by rsommer           #+#    #+#             */
/*   Updated: 2025/01/06 15:00:00 by rsommer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_pixel(t_game *game, int x, int y, int color)
{
	int	screen_x;
	int	screen_y;

	screen_x = MINIMAP_X + x;
	screen_y = MINIMAP_Y + y;
	if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT)
		put_pixel(&game->img, screen_x, screen_y, color);
}

static int	get_map_color(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->map_width || map_y < 0
		|| map_y >= game->map_height)
		return (0x000000);
	if (game->map[map_y][map_x] == '1')
		return (0xFFFFFF);
	return (0x666666);
}

void	draw_minimap_background(t_game *game)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			map_x = (int)(game->player.x) - MINIMAP_SIZE / (2 * MINIMAP_SCALE)
				+ x / MINIMAP_SCALE;
			map_y = (int)(game->player.y) - MINIMAP_SIZE / (2 * MINIMAP_SCALE)
				+ y / MINIMAP_SCALE;
			draw_minimap_pixel(game, x, y, get_map_color(game, map_x, map_y));
			x++;
		}
		y++;
	}
}
